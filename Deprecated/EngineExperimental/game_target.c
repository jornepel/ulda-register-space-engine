/* game_target.c — Simulatie van een actieve Windows Game-Thread (Clean Build) */
#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void SimulateGameRenderLoop(void) {
    printf("[Game Engine] Start actieve 3D render thread...\n");
    
    /* Laad de lokale proxy DLL in */
    HMODULE hD3D = LoadLibraryA("d3d11.dll");
    if (!hD3D) {
        printf("[Fatal] Kan proxy d3d11.dll niet vinden in uitvoermap.\n");
        return;
    }

    /* Haal het generieke adres op */
    FARPROC raw_proc = GetProcAddress(hD3D, "Hooked_DrawIndexed");
    if (raw_proc) {
        /* Bypas de GCC type-check via een intermediate void-pointer cast */
        void *bridge_ptr = (void *)(uintptr_t)raw_proc;
        void (*Proxy_DrawIndexed)(unsigned int, unsigned int, int) = 
            (void (*)(unsigned int, unsigned int, int))bridge_ptr;

        /* Vuur de geïntercepteerde call af zonder afrondingsruis */
        Proxy_DrawIndexed(3, 0, 0); 
    } else {
        printf("[Error] Hooked function entry point niet gevonden.\n");
    }

    FreeLibrary(hD3D);
}

int main(void) {
    printf("=== LIVE INJECTIE TEST: VERIFIËREN AFRONDINGSRUIS ===\n");
    SimulateGameRenderLoop();
    return 0;
}
