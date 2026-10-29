"""
ulda_visual.py — Live 3D Topological Graphics Pipeline Grid Projector.
Maps exact ℤ[φ] structural coordinates onto a live terminal isometric map canvas.
"""
import os
import sys
import ctypes
import math
import time

# 1. Load the shared library built by your Makefile
lib_name = "libulda.dylib" if sys.platform == "darwin" else "libulda.so"
lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), lib_name))

if not os.path.exists(lib_path):
    print(f"[Error] Shared library missing. Run 'make lib' first.")
    sys.exit(1)

ulda = ctypes.CDLL(lib_path)

# 2. Set up the argument signatures for the flat C interface
ulda.chord_sqnorm_flat.argtypes = [
    ctypes.c_longlong, ctypes.c_longlong, # Ox (a, b)
    ctypes.c_longlong, ctypes.c_longlong, # Oy (a, b)
    ctypes.c_longlong, ctypes.c_longlong, # Oz (a, b)
    ctypes.c_longlong, ctypes.c_longlong, # Qx (a, b)
    ctypes.c_longlong, ctypes.c_longlong, # Qy (a, b)
    ctypes.c_longlong, ctypes.c_longlong, # Qz (a, b)
    ctypes.POINTER(ctypes.c_longlong),    # out_a
    ctypes.POINTER(ctypes.c_longlong)     # out_b
]
ulda.chord_sqnorm_flat.restype = None

# 3. Canvas Screen Layout Geometry
WIDTH, HEIGHT = 70, 25
PHI_FLOAT = (1.0 + math.sqrt(5.0)) / 2.0

def project_iso(q_flat):
    """Converts 3D Z[phi] discrete coordinates cleanly into 2D terminal screenspace."""
    # q_flat matches: [Qx_a, Qx_b, Qy_a, Qy_b, Qz_a, Qz_b]
    fx = q_flat[0] + q_flat[1] * PHI_FLOAT
    fy = q_flat[2] + q_flat[3] * PHI_FLOAT
    fz = q_flat[4] + q_flat[5] * PHI_FLOAT
    
    # Isometric matrix projection vectors
    screen_x = int(WIDTH / 2 + (fx - fy) * math.cos(math.pi / 6) * 2.2)
    screen_y = int(HEIGHT / 2 + (fx + fy) * math.sin(math.pi / 6) * 1.1 - fz * 0.8)
    return screen_x, screen_y

# 4. Synchronized state vectors tracking the primary elemental waves
# Mapped as exact array components: [x.a, x.b, y.a, y.b, z.a, z.b]
positions = [
    # Torus A: Anchored directly on the Invariant Mirror Plane chord
    {
        "O": [0, 0, 0, 0, 0, 0], 
        "Q": [0, 0, -1, 1, 0, 1], 
        "gear": 1,  
        "sym": "A", 
        "color": "\033[1;31m", 
        "label": "Riemann (Location Rounding half-step)"
    },
    
    # Torus B: Anchored directly on the Invariant Rollover Antipodal chord
    {
        "O": [0, 0, 0, 0, 0, 0], 
        "Q": [-1, 0, -1, 0, -1, 0], 
        "gear": -1, 
        "sym": "B", 
        "color": "\033[1;33m", 
        "label": "BSD (Arithmetic Count Saturation)"
    },
    
    # Torus C: Parallel Counter-Rotational Copy of the Mirror State
    {
        "O": [0, 0, 0, 0, 0, 0], 
        "Q": [0, 0, -1, 1, 0, 1], 
        "gear": -1, 
        "sym": "C", 
        "color": "\033[1;34m", 
        "label": "Parallel Mirror Invariant"
    },
    
    # Torus D: Parallel Counter-Rotational Copy of the Rollover State 
    {
        "O": [0, 0, 0, 0, 0, 0], 
        "Q": [-1, 0, -1, 0, -1, 0], 
        "gear": 1,  
        "sym": "D", 
        "color": "\033[1;35m", 
        "label": "Hierarchy (Scale Ratio Mass Collapse)"
    }
]

out_a = ctypes.c_longlong(0)
out_b = ctypes.c_longlong(0)

print("\033[2J") # Initial canvas wipe

try:
    tick = 0
    while True:
        # Initialize an empty coordinate screen frame buffer
        canvas = [[" " for _ in range(WIDTH)] for _ in range(HEIGHT)]
        
        # Plot central reference grid lines
        for idx in range(1, WIDTH - 1): canvas[int(HEIGHT/2)][idx] = "·"
        for idx in range(1, HEIGHT - 1): canvas[idx][int(WIDTH/2)] = "·"
        
        for p in positions:
            # Drive the vertex coords forward along the mechanical gear shifts
            p["Q"][0] += p["gear"]  # Update Qx_a
            p["Q"][3] += p["gear"]  # Update Qy_b
            
            # Verify boundary metrics natively via your compiled flat C engine
            ulda.chord_sqnorm_flat(
                p["O"][0], p["O"][1], p["O"][2], p["O"][3], p["O"][4], p["O"][5],
                p["Q"][0], p["Q"][1], p["Q"][2], p["Q"][3], p["Q"][4], p["Q"][5],
                ctypes.byref(out_a), ctypes.byref(out_b)
            )
            
            # Mirror Invariant Check (3 + 1φ) triggers direction gear snap
            if out_a.value == 3 and out_b.value == 1:
                p["gear"] *= -1
                
            # Antipodal Rollover Check (7 + 3φ) resets coordinates to horizon seed
            if out_a.value == 7 and out_b.value == 3:
                p["Q"] = [0, 0, 0, 0, 0, 0]
                
            # Project down to screen pixels
            sx, sy = project_iso(p["Q"])
            if 0 <= sx < WIDTH and 0 <= sy < HEIGHT:
                canvas[sy][sx] = f"{p['color']}{p['sym']}\033[0m"
                
        # Flush the buffer out to stdout
        output = ["\033[H"]
        output.append(f"=== ULDA EMULATOR RENDER LAYER | Frame: {tick:04d} | Math: Exact ℤ[φ] ===\n")
        for row in canvas:
            output.append("".join(row) + "\n")
            
        sys.stdout.write("".join(output))
        sys.stdout.flush()
        
        tick += 1
        time.sleep(0.07)

except KeyboardInterrupt:
    print("\n[Graphics Pipeline Detached] Map screen cleared.")
