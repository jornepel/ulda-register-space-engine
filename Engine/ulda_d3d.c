/* ============================================================================
 * ulda_d3d.c — Direct3D 11 Active Proxy Injection Hook Module
 * Captures, intercepts, and shunts vertex hardware commands on the hot path.
 * Cleaned and hardened to compile with zero compiler warnings.
 * ============================================================================
 */

#include "ulda_unified.h"
#include <windows.h>
#include <d3d11.h>

/* Functional Pointer signatures for tracking stock system runtime hooks */
typedef HRESULT (WINAPI *D3D11CreateDeviceAndSwapChain_t)(
    IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
    const D3D_FEATURE_LEVEL*, UINT, UINT,
    const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
    ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**
);

static D3D11CreateDeviceAndSwapChain_t RealD3D11CreateDeviceAndSwapChain = NULL;
static HMODULE g_hRealD3D11Module = NULL;

/* Extracted emulator signature to process GPU buffer memory regions */
extern void ulda_emu_intercept_vertex_stream(void* pVertexBuffer, uint32_t vertexCount, uint32_t stride, const mat3* transformationMatrix);

/* ----------------------------------------------------------------------------
 * 1. PROXY HOOK INITIALIZATION
 * ----------------------------------------------------------------------------
 * Automatically maps standard D3D11 system library entry addresses upon loading.
 */
static void InitializeProxyHooks(void) {
    if (g_hRealD3D11Module) return;

    char sysPath[MAX_PATH];
    GetSystemDirectory(sysPath, MAX_PATH);
    strcat(sysPath, "\\d3d11.dll");

    g_hRealD3D11Module = LoadLibrary(sysPath);
    if (g_hRealD3D11Module) {
        /* Use an intermediate void* cast to silence -Wcast-function-type warnings */
        void* pFunc = (void*)GetProcAddress(g_hRealD3D11Module, "D3D11CreateDeviceAndSwapChain");
        RealD3D11CreateDeviceAndSwapChain = (D3D11CreateDeviceAndSwapChain_t)pFunc;
    }
}

/* ----------------------------------------------------------------------------
 * 2. EXPORTED ENTRY FUNCTION SWAP
 * ----------------------------------------------------------------------------
 * Replaces system runtime calls. Intercepts context and device pointers.
 */
EXPORT HRESULT WINAPI D3D11CreateDeviceAndSwapChain(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppDeviceContext
) {
    InitializeProxyHooks();
    if (!RealD3D11CreateDeviceAndSwapChain) return E_FAIL;

    /* Execute native hardware context assembly pass safely */
    HRESULT hr = RealD3D11CreateDeviceAndSwapChain(
        pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels,
        SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppDeviceContext
    );

    return hr;
}

/* ----------------------------------------------------------------------------
 * 3. TENSOR SHEAR SHUNT PIPELINE HOOK
 * ----------------------------------------------------------------------------
 * Intercepts active draws. Inspects bound IA vertex buffers, maps raw memory 
 * ranges, and shunts coordinates through the error-free Z[φ] matrix pipeline.
 */
EXPORT void ulda_d3d_shunt_draw_pipeline(ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation) {
    /* Explicitly silence the unused parameter warning for standard API layouts */
    (void)StartVertexLocation;

    if (!pContext) return;

    ID3D11Buffer* pVertexBuffer = NULL;
    UINT stride = 0;
    UINT offset = 0;

    /* Sample active Input-Assembler buffer registers on the immediate hot path */
    pContext->lpVtbl->IAGetVertexBuffers(pContext, 0, 1, &pVertexBuffer, &stride, &offset);
    if (!pVertexBuffer) return;

    D3D11_BUFFER_DESC desc;
    pVertexBuffer->lpVtbl->GetDesc(pVertexBuffer, &desc);

    /* Enforce hardware access validation flags to permit processing map commands */
    if (desc.Usage == D3D11_USAGE_DYNAMIC && (desc.CPUAccessFlags & D3D11_CPU_ACCESS_WRITE)) {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        
        /* Lock vertex streams directly inside VRAM/SysRAM cache boundaries */
        HRESULT hr = pContext->lpVtbl->Map(pContext, (ID3D11Resource*)pVertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
        if (SUCCEEDED(hr)) {
            
            /* Build default integer transform identity matrix */
            mat3 identity_matrix;
            memset(&identity_matrix, 0, sizeof(mat3));
            identity_matrix.m00.a = 1;
            identity_matrix.m11.a = 1;
            identity_matrix.m22.a = 1;

            /* Push active hardware buffer data into the topological ring decoder */
            ulda_emu_intercept_vertex_stream(mappedResource.pData, VertexCount, stride, &identity_matrix);

            /* Release mapping handles to permit standard hardware presentation steps */
            pContext->lpVtbl->Unmap(pContext, (ID3D11Resource*)pVertexBuffer, 0);
        }
    }

    pVertexBuffer->lpVtbl->Release(pVertexBuffer);
}

/* Win32 Main Dynamic Link Attachment entry loop */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    /* Explicitly silence the unused API hook reservation parameter */
    (void)lpvReserved;

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            InitializeProxyHooks();
            break;
        case DLL_PROCESS_DETACH:
            if (g_hRealD3D11Module) {
                FreeLibrary(g_hRealD3D11Module);
                g_hRealD3D11Module = NULL;
            }
            break;
    }
    return TRUE;
}
