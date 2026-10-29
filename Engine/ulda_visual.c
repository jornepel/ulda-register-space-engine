
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ulda.h"
#include "puzzles.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define VECTOR_LANES  6
#define TORUS_COUNT   4
#define GATE_COUNT    8

#define ULDA_PI 3.14159265358979323846
#define PHI_FLOAT 1.618033988749895

typedef long long i64;

typedef struct {
    const char* name;
    i64 coords[VECTOR_LANES];
    int rejected;
} RibGate;

typedef struct {
    i64 O[VECTOR_LANES];
    i64 Q[VECTOR_LANES];
    i64 seed_Q[VECTOR_LANES];
    int gear;
    int seed_gear;
    char sym;
    COLORREF color;
    const char* label;
} TorusAgent;

// Static workspace structures
static RibGate g_gates[GATE_COUNT];
static TorusAgent g_agents[TORUS_COUNT];
static int g_frame_tick = 0;

void chord_sqnorm_flat(
    i64 Ox_a, i64 Ox_b, i64 Oy_a, i64 Oy_b, i64 Oz_a, i64 Oz_b,
    i64 Qx_a, i64 Qx_b, i64 Qy_a, i64 Qy_b, i64 Qz_a, i64 Qz_b,
    i64* out_a, i64* out_b
);

/**
 * Projects 3D Z[phi] discrete coordinates cleanly into 2D screenspace pixel positions.
 */
void ProjectIsometric(const i64* q_flat, int* sx, int* sy) {
    double fx = (double)q_flat[0] + (double)q_flat[1] * PHI_FLOAT;
    double fy = (double)q_flat[2] + (double)q_flat[3] * PHI_FLOAT;
    double fz = (double)q_flat[4] + (double)q_flat[5] * PHI_FLOAT;
    
    *sx = (int)((SCREEN_WIDTH / 2.0) + (fx - fy) * cos(ULDA_PI / 6.0) * 45.0);
    *sy = (int)((SCREEN_HEIGHT / 2.0) + (fx + fy) * sin(ULDA_PI / 6.0) * 25.0 - fz * 15.0);
}

/**
 * Windows State Calculation & Render Paint Cycle with Deep Space Mutations
 */
void DrawUldaField(HDC hdc) {
    i64 out_a = 0, out_b = 0;

    // Reset gate properties for this frame refresh
    for (int i = 0; i < GATE_COUNT; i++) g_gates[i].rejected = 0;

    // Process discrete kinematics math prior to drawing
    for (int i = 0; i < TORUS_COUNT; i++) {
        TorusAgent* p = &g_agents[i];
        
        // --- ADVANCE STEP WITH COORDINATE FIELD MUTATIONS ---
        double t = (double)g_frame_tick * 0.04;
        
        // 1. Cross-Talk Shear: Axis velocities modulate each other dynamically [S^-2]
        i64 shear_x = (i64)(p->gear * 4.0 * cos(t + i * (ULDA_PI / 2.0)));
        i64 shear_y = (i64)(p->gear * 4.0 * sin(t + i * (ULDA_PI / 2.0)));
        
        p->Q[0] += shear_x; // Shift X_a
        p->Q[2] += shear_y; // Shift Y_a
        
        // 2. Quadratic Fractal Twist: Let the Z axis spin faster on high stress
        p->Q[4] += (i64)(p->gear * 2.0 * sin(t * 2.5 + i)); // Shift Z_a

        // Execute exact metrics pass through the unrolled engine interface
        chord_sqnorm_flat(
            p->O[0], p->O[1], p->O[2], p->O[3], p->O[4], p->O[5],
            p->Q[0], p->Q[1], p->Q[2], p->Q[3], p->Q[4], p->Q[5],
            &out_a, &out_b
        );

        // Grade claim rejections against the 8 fixed gates
        for (int g = 0; g < GATE_COUNT; g++) {
            i64 dist = llabs(p->Q[0] - g_gates[g].coords[0]) + llabs(p->Q[2] - g_gates[g].coords[2]);
            if (dist > 8 && g_frame_tick % 12 == g) {
                g_gates[g].rejected = 1;
            }
        }

        // Mirror Plane Invariant boundary gear snap (3 + 1φ)
        if (out_a == 3 && out_b == 1) p->gear *= -1;
        
        // 3. The Bounded Attractor Collapse: Curvature compression
        // Instead of instantly resetting, compress space vectors to warp back into spirals
        if (out_a >= 4500 || llabs(p->Q[0]) > 35) {
            p->Q[0] = (p->Q[0] * 2) / 3; // Strict 2/3 integer scale compression
            p->Q[2] = (p->Q[2] * 2) / 3;
            p->Q[4] = (p->Q[4] * 2) / 3;
            p->gear *= -1; // Reverse local rotational matrix flow direction
        }
    }

    // --- DRAW NATIVE GRAPHICS LAYERS ---
    HPEN axesPen = CreatePen(PS_SOLID, 1, RGB(40, 50, 65));
    HPEN oldPen = (HPEN)SelectObject(hdc, axesPen);
    MoveToEx(hdc, SCREEN_WIDTH / 2, 50, NULL);
    LineTo(hdc, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
    MoveToEx(hdc, 50, SCREEN_HEIGHT / 2, NULL);
    LineTo(hdc, SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);

    // Draw Fixed 8-Rib Gates
    for (int i = 0; i < GATE_COUNT; i++) {
        int gx, gy;
        ProjectIsometric(g_gates[i].coords, &gx, &gy);
        COLORREF gateColor = g_gates[i].rejected ? RGB(255, 60, 60) : RGB(60, 255, 60);

        HBRUSH gateBrush = CreateSolidBrush(g_gates[i].rejected ? RGB(60, 20, 20) : RGB(20, 60, 20));
        HPEN gatePen = CreatePen(PS_SOLID, 2, gateColor);
        
        SelectObject(hdc, gateBrush);
        SelectObject(hdc, gatePen);
        Ellipse(hdc, gx - 16, gy - 16, gx + 16, gy + 16);
        
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);
        
        wchar_t wName[4];
        swprintf(wName, 4, L"G%d", i + 1);
        DrawTextW(hdc, wName, -1, &(RECT){gx - 10, gy - 7, gx + 10, gy + 7}, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        if (g_gates[i].rejected) {
            SetTextColor(hdc, RGB(255, 60, 60));
            DrawTextW(hdc, L"VETO", -1, &(RECT){gx - 20, gy + 18, gx + 20, gy + 32}, DT_CENTER | DT_SINGLELINE);
        }

        DeleteObject(gateBrush);
        DeleteObject(gatePen);
    }

    // Draw Traveling Wave Agents and Geometric Strings
    for (int i = 0; i < TORUS_COUNT; i++) {
        int ax, ay, ox, oy;
        ProjectIsometric(g_agents[i].Q, &ax, &ay);
        ProjectIsometric(g_agents[i].O, &ox, &oy);

        // Draw structural chord vectors connecting back to origin
        HPEN linePen = CreatePen(PS_SOLID, 1, g_agents[i].color);
        SelectObject(hdc, linePen);
        MoveToEx(hdc, ox, oy, NULL);
        LineTo(hdc, ax, ay);

        // Draw particle nodes
        HBRUSH agentBrush = CreateSolidBrush(g_agents[i].color);
        HPEN agentPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        SelectObject(hdc, agentBrush);
        SelectObject(hdc, agentPen);
        Ellipse(hdc, ax - 10, ay - 10, ax + 10, ay + 10);

        SetTextColor(hdc, RGB(0, 0, 0));
        wchar_t wSym[2] = { (wchar_t)g_agents[i].sym, L'\0' };
        DrawTextW(hdc, wSym, -1, &(RECT){ax - 8, ay - 8, ax + 8, ay + 8}, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        DeleteObject(agentBrush);
        DeleteObject(agentPen);
        DeleteObject(linePen);
    }

    // Render HUD Info Box
    HBRUSH hudBrush = CreateSolidBrush(RGB(20, 25, 35));
    SelectObject(hdc, hudBrush);
    Rectangle(hdc, 15, 15, 485, 65);
    
    SetTextColor(hdc, RGB(0, 255, 255));
    wchar_t hudTitle[128];
    swprintf(hudTitle, 128, L"ULDA MUTATED COSMOS FIELD | Ticks: %04d", g_frame_tick);
    DrawTextW(hdc, hudTitle, -1, &(RECT){25, 22, 475, 42}, DT_LEFT | DT_SINGLELINE);
    
    SetTextColor(hdc, RGB(200, 200, 200));
    DrawTextW(hdc, L"Subsystem: Non-Linear Coordinate Field Mutation [Orbits Active]", -1, &(RECT){25, 42, 475, 58}, DT_LEFT | DT_SINGLELINE);

    SelectObject(hdc, oldPen);
    DeleteObject(axesPen);
    DeleteObject(hudBrush);

    g_frame_tick++;
}

/**
 * Core Win32 Windows Event Callback Router Handler
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMem = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
            HBITMAP hOldBm = (HBITMAP)SelectObject(hdcMem, hbmMem);

            HBRUSH bgBrush = CreateSolidBrush(RGB(10, 14, 20));
            FillRect(hdcMem, &(RECT){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, bgBrush);
            DeleteObject(bgBrush);

            DrawUldaField(hdcMem);

            BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, hOldBm);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_TIMER:
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    (void)hPrev; (void)lpCmd; (void)nShow;

    RibGate initial_gates[GATE_COUNT] = {
        {"G1", { 1, 0,  1, 0,  1, 0}, 0}, {"G2", { 1, 0,  1, 0, -1, 0}, 0},
        {"G3", { 1, 0, -1, 0,  1, 0}, 0}, {"G4", { 1, 0, -1, 0, -1, 0}, 0},
        {"G5", {-1, 0,  1, 0,  1, 0}, 0}, {"G6", {-1, 0,  1, 0, -1, 0}, 0},
        {"G7", {-1, 0, -1, 0,  1, 0}, 0}, {"G8", {-1, 0, -1, 0, -1, 0}, 0}
    };
    memcpy(g_gates, initial_gates, sizeof(g_gates));

    TorusAgent initial_agents[TORUS_COUNT] = {
        {{0,0,0,0,0,0}, {0, 0, -1, 1, 0, 1}, {0, 0, -1, 1, 0, 1}, 1, 1, 'A', RGB(255, 50, 50), "Riemann"},
        {{0,0,0,0,0,0}, {-1, 0, -1, 0, -1, 0}, {-1, 0, -1, 0, -1, 0}, -1, -1, 'B', RGB(255, 165, 0), "BSD"},
        {{0,0,0,0,0,0}, {0, 0, -1, 1, 0, 1}, {0, 0, -1, 1, 0, 1}, -1, -1, 'C', RGB(50, 180, 255), "Parallel Mirror"},
        {{0,0,0,0,0,0}, {-1, 0, -1, 0, -1, 0}, {-1, 0, -1, 0, -1, 0}, 1, 1, 'D', RGB(200, 50, 255), "Hierarchy"}
    };
    memcpy(g_agents, initial_agents, sizeof(g_agents));

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hbrBackground = NULL;
    wc.lpszClassName = L"ULDA_VISUAL_CLASS";

    RegisterClassW(&wc);
    
    // Hardened complete 12-argument Win32 WinMain layout
    HWND hwnd = CreateWindowExW(
        0, 
        wc.lpszClassName, 
        L"ULDA FIELD MONITOR PROJECTOR",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        SCREEN_WIDTH + 16, SCREEN_HEIGHT + 39,
        NULL, NULL, hInst, NULL
    );

    SetTimer(hwnd, 1, 16, NULL); // Sync update frame rate (~60 FPS)

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}