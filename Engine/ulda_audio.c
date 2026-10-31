/* ============================================================================
 * ulda_audio.c — Real-Time Audio Synthesis & Phase Oscillator Module
 * Translates discrete angular rotations into raw PCM audio sample streams.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define PI_APPROX 3.1415926535f

/* Audio State Register tracking phase progression over time */
typedef struct {
    uint32_t current_sample;
    zphi frequency_chord;
    float phase_accumulator;
} ULDA_AUDIO_CHANNEL;

/* ----------------------------------------------------------------------------
 * AUDIO BUFFER INJECTOR
 * ----------------------------------------------------------------------------
 * Fills a raw memory buffer with 16-bit signed integer PCM audio samples.
 * Syncs pitch directly to the scalar field norms of your coordinate keys.
 */
EXPORT void ulda_audio_render_pcm16(
    void* pBuffer, 
    uint32_t bufferSizeSamples, 
    int64_t a_freq, 
    int64_t b_freq
) {
    if (!pBuffer || bufferSizeSamples == 0) return;

    int16_t* pOutSamples = (int16_t*)pBuffer;
    zphi freq_key = {a_freq, b_freq};
    
    /* Calculate the frequency from the discrete ring norm */
    int64_t metric_norm = chord_sqnorm(freq_key);
    if (metric_norm <= 0) metric_norm = 432; /* Default to A=432Hz safety register */

    /* Frequency scaling constraint matched to the 12-step phalanx ladder */
    float target_frequency = (float)(metric_norm % 1000);
    float phase_increment = (2.0f * PI_APPROX * target_frequency) / (float)SAMPLE_RATE;
    static float running_phase = 0.0f;

    for (uint32_t i = 0; i < bufferSizeSamples; ++i) {
        /* Generate raw longitudinal vector push (sinusoidal compression) */
        float sample_value = sinf(running_phase);
        
        /* Normalize and clip into a 16-bit signed integer channel slot */
        pOutSamples[i] = (int16_t)(sample_value * 32767.0f);
        
        /* Step the phase forward along the rotational tracking arc */
        running_phase += phase_increment;
        if (running_phase >= 2.0f * PI_APPROX) {
            running_phase -= 2.0f * PI_APPROX;
        }
    }
}
