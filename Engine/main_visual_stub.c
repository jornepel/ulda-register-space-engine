/* ============================================================================
 * main_visual_stub.c - Desktop Application Entry Stub with Live Audio Output
 * Instantiates the canvas loop, opens WinMM WaveOut sound hardware streams.
 * Hardened to standard ASCII characters to eliminate compiler errors.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <string.h>

/* Visual, Audio, and Network references from external modules */
extern bool ulda_visual_init_window(void);
extern void ulda_visual_render_frame(const vec3* vertex_array, uint32_t vertex_count);
extern void ulda_visual_shutdown(void);
extern void ulda_telemetry_transmit_json(vec3 v);
extern void ulda_audio_render_pcm16(void* pBuffer, uint32_t bufferSizeSamples, int64_t a_freq, int64_t b_freq);

#define AUDIO_BUFFER_SAMPLES 1024
int16_t g_AudioBuffer[AUDIO_BUFFER_SAMPLES];

int main(void) {
    /* Step 1: Initialize the Graphical Viewport Canvas */
    if (!ulda_visual_init_window()) {
        return 1;
    }

    /* --------------------------------------------------------------------
     * NATIVE WINDOWS HARDWARE AUDIO INITIALIZATION
     * --------------------------------------------------------------------
     * Sets up a standard 44.1 kHz, 16-bit Mono sound streaming device.
     * --------------------------------------------------------------------
     */
    HWAVEOUT hWaveOut;
    WAVEFORMATEX waveFormat;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 1; /* Mono channel */
    waveFormat.nSamplesPerSec = 44100; /* 44.1 kHz standard CD sampling rate */
    waveFormat.wBitsPerSample = 16; /* 16-bit signed integer depth */
    waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    waveFormat.cbSize = 0;

    // Open the default Windows audio output device
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        return 1; /* Sound hardware was unavailable or blocked */
    }

    /* Set up double-buffered WaveOut header structures to prevent audio stutter */
    WAVEHDR waveHdr;
    memset(&waveHdr, 0, sizeof(WAVEHDR));
    waveHdr.lpData = (LPSTR)g_AudioBuffer;
    waveHdr.dwBufferLength = AUDIO_BUFFER_SAMPLES * sizeof(int16_t);

    const uint32_t vertex_count = 4;
    vec3 orbit_ring[4];
    
    /* Setup initial 4-point structural layout inside the viewport bounds */
    orbit_ring[0] = (vec3){{100000, 0}, {100000, 0}, {0, 0}};
    orbit_ring[1] = (vec3){{-100000, 0}, {100000, 0}, {0, 0}};
    orbit_ring[2] = (vec3){{-100000, 0}, {-100000, 0}, {0, 0}};
    orbit_ring[3] = (vec3){{100000, 0}, {-100000, 0}, {0, 0}};

    /* Construct a stabilized phase-rotation matrix to step the angles */
    mat3 phase_rotation;
    memset(&phase_rotation, 0, sizeof(mat3));
    
    /* Clean 90-degree step matrix to cycle through the 4 internal struts */
    phase_rotation.m00 = (zphi){0, 0};   /* x_out = 0*x */
    phase_rotation.m01 = (zphi){-1, 0};  /* x_out = -1*y */
    phase_rotation.m10 = (zphi){1, 0};   /* y_out = 1*x */
    phase_rotation.m11 = (zphi){0, 0};   /* y_out = 0*y */
    phase_rotation.m22 = (zphi){1, 0};   /* Keep Z depth fixed */

    MSG msg = {0};
    bool running = true;

    while (running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        /* Slide coordinates along the struts inside our exact algebraic ring */
        for (uint32_t i = 0; i < vertex_count; ++i) {
            orbit_ring[i] = mat3_mul_vec3(phase_rotation, orbit_ring[i]);
            ulda_telemetry_transmit_json(orbit_ring[i]);
        }

        /* Calculate sound samples directly from the spinning geometric vector nodes */
        ulda_audio_render_pcm16(
            g_AudioBuffer, 
            AUDIO_BUFFER_SAMPLES, 
            orbit_ring[0].x.a, 
            orbit_ring[0].y.a
        );

        /* PUSH SAMPLES TO HARDWARE: Stream the sound buffer out to your physical speakers */
        waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));

        /* Paint current phase state onto the desktop monitor canvas */
        ulda_visual_render_frame(orbit_ring, vertex_count);
        
        /* Brief sleep to allow the audio hardware to process the memory chunk */
        Sleep(22); 
        
        /* Clean up the audio driver header before the next iteration loop */
        while (!(waveHdr.dwFlags & WHDR_DONE)) {
            Sleep(1);
        }
        waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    }

    /* Shutdown Lifecycles */
    waveOutClose(hWaveOut);
    ulda_visual_shutdown();
    return 0;
}
