/* ============================================================================
 * ulda_visual.c — Win32 Canvas Renderer & Orbital Geometry Projector
 * Maps discrete 3D ring matrices onto live Win32 GDI screen buffers.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <windows.h>
#include <stdbool.h>

/* Window Context Frame Elements */
static HWND g_hWnd = NULL;
static HDC g_hDC = NULL;
static int g_screenWidth = 800;
static int g_screenHeight = 600;

/* ----------------------------------------------------------------------------
 * GRAPHICAL SCREEN PROJECTION ENGINE
 * ----------------------------------------------------------------------------
 */
static void project_vertex_to_screen(const vec3* v, int* out_x, int* out_y) {
    const float phi_approx = 1.6180339887f;
    const float scale_down = 500000.0f; /* Normalization factor */

    /* Approximate the 3D ring components back into raw viewport spaces */
    float fx = ((float)v->x.a + ((float)v->x.b * phi_approx)) / scale_down;
    float fy = ((float)v->y.a + ((float)v->y.b * phi_approx)) / scale_down;
    float fz = ((float)v->z.a + ((float)v->z.b * phi_approx)) / scale_down;

    /* Simple perspective matrix projection with Z-depth division shift */
    float distance = 4.0f;
    float perspective = 1.0f / (distance - fz);

    *out_x = (int)((float)g_screenWidth / 2.0f + (fx * perspective * (float)g_screenWidth * 0.5f));
    *out_y = (int)((float)g_screenHeight / 2.0f - (fy * perspective * (float)g_screenHeight * 0.5f));
}

/* Win32 Callback Window Procedure Handler */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

/* ----------------------------------------------------------------------------
 * LIVE WINDOW PRESENTATION RENDERING LOOP
 * ----------------------------------------------------------------------------
 */
EXPORT void ulda_visual_render_frame(const vec3* vertex_array, uint32_t vertex_count) {
    if (!g_hDC || !vertex_array || vertex_count == 0) return;

    /* Clear the frame background to generate an active clean drawing pool */
    HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(10, 14, 20));
    RECT clientRect = { 0, 0, g_screenWidth, g_screenHeight };
    FillRect(g_hDC, &clientRect, hBackgroundBrush);
    DeleteObject(hBackgroundBrush);

    /* Use a high-visibility glowing color track for the matrix struts */
    HPEN hStrutPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 150));
    HPEN hOldPen = (HPEN)SelectObject(g_hDC, hStrutPen);

    for (uint32_t i = 0; i < vertex_count; ++i) {
        int screen_x, screen_y;
        project_vertex_to_screen(&vertex_array[i], &screen_x, &screen_y);

        /* Paint a localized pixel dot at the precise coordinate cross target */
        if (i == 0) {
            MoveToEx(g_hDC, screen_x, screen_y, NULL);
        } else {
            LineTo(g_hDC, screen_x, screen_y);
        }
        
        /* Draw an individual node indicator box at each vertex location */
        Rectangle(g_hDC, screen_x - 3, screen_y - 3, screen_x + 3, screen_y + 3);
    }

    SelectObject(g_hDC, hOldPen);
    DeleteObject(hStrutPen);
}

EXPORT bool ulda_visual_init_window(void) {
    HINSTANCE hInst = GetModuleHandle(NULL);
    
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInst;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = "ULDA_VISUAL_CANVAS";

    if (!RegisterClassEx(&wcex)) return false;

    g_hWnd = CreateWindow("ULDA_VISUAL_CANVAS", "ℤ[φ]³ Geometry Projector", 
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
                          g_screenWidth, g_screenHeight, NULL, NULL, hInst, NULL);

    if (!g_hWnd) return false;

    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);
    g_hDC = GetDC(g_hWnd);
    
    return true;
}

EXPORT void ulda_visual_shutdown(void) {
    if (g_hWnd && g_hDC) {
        ReleaseDC(g_hWnd, g_hDC);
        DestroyWindow(g_hWnd);
    }
}
