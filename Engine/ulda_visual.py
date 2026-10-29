import os
import sys
import ctypes
import math
import time

# 1. Load the shared library built by your Makefile
lib_name = "libulda.dylib" if sys.platform == "darwin" else "libulda.so"
lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), lib_name))

if not os.path.exists(lib_path):
    print(f"[Error] Shared library not found. Run 'make lib' first.")
    sys.exit(1)

ulda = ctypes.CDLL(lib_path)

# 2. Define the argument mapping for the flat C shim
ulda.chord_sqnorm_flat.argtypes = [
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.c_longlong, ctypes.c_longlong,
    ctypes.POINTER(ctypes.c_longlong),
    ctypes.POINTER(ctypes.c_longlong)
]
ulda.chord_sqnorm_flat.restype = None

# 3. Canvas Geometry for Terminal Output
WIDTH, HEIGHT = 70, 30
PHI_FLOAT = (1.0 + math.sqrt(5.0)) / 2.0  # Floating-point equivalent used ONLY for rendering projection

def project_iso(x, y, z):
    """Projects 3D Z[phi] spatial coordinates into 2D terminal screenspace."""
    # Convert exact Z[phi] integers to floating scale for display layout
    fx = x[0] + x[1] * PHI_FLOAT
    fy = y[0] + y[1] * PHI_FLOAT
    fz = z[0] + z[1] * PHI_FLOAT
    
    # Standard isometric transformation matrix
    screen_x = int(WIDTH / 2 + (fx - fy) * math.cos(math.pi / 6) * 2.5)
    screen_y = int(HEIGHT / 2 + (fx + fy) * math.sin(math.pi / 6) * 1.2 - fz * 1.0)
    return screen_x, screen_y

# Synchronized state vectors tracking the primary elemental waves
# Mapped as exact array components: [x.a, x.b, y.a, y.b, z.a, z.b]
positions = [
    # Torus A: Anchored directly on the Invariant Mirror Plane chord
    {"O":, "Q": [0,0, -1,1, 0,1], "gear": 1,  "sym": "A"},
    
    # Torus B: Anchored directly on the Invariant Rollover Antipodal chord
    {"O":, "Q": [-1,0, -1,0, -1,0], "gear": -1, "sym": "B"},
    
    # Torus C: Parallel Counter-Rotational Copy of the Mirror State
    {"O":, "Q": [0,0, -1,1, 0,1], "gear": -1, "sym": "C"},
    
    # Torus D: Parallel Counter-Rotational Copy of the Rollover State
    {"O":, "Q": [-1,0, -1,0, -1,0], "gear": 1,  "sym": "D"}
]


out_a = ctypes.c_longlong(0)
out_b = ctypes.c_longlong(0)

print("\033[2J") # Clear console screen layout

try:
    tick = 0
    while True:
        # Initialize an empty terminal canvas frame
        canvas = [[" " for _ in range(WIDTH)] for _ in range(HEIGHT)]
        
        # Draw central structural axes grid references
        for idx in range(1, WIDTH - 1): canvas[int(HEIGHT/2)][idx] = "·"
        for idx in range(1, HEIGHT - 1): canvas[idx][int(WIDTH/2)] = "·"
        
        # Step through the network mesh state
        for node in nodes:
            # Shift the coordinate components dynamically based on gear polarity
            node["Qx"][0] += node["gear"]
            node["Qy"][1] += node["gear"]
            
            # Execute calculation via your compiled flat C engine
            ulda.chord_sqnorm_flat(
                node["O"][0], node["O"][1], node["Oy"][0], node["Oy"][1], node["Oz"][0], node["Oz"][1],
                node["Qx"][0], node["Qx"][1], node["Qy"][0], node["Qy"][1], node["Qz"][0], node["Qz"][1],
                ctypes.byref(out_a), ctypes.byref(out_b)
            )
            
            # Boundary Collision Invariant: Mirror Plane (3 + 1φ)
            if out_a.value == 3 and out_b.value == 1:
                node["gear"] *= -1 # Reverse rotation matrix flow direction
                
            # Boundary Collision Invariant: Antipodal Rollover (7 + 3φ)
            if out_a.value == 7 and out_b.value == 3:
                node["Qx"] = [1, 0] # Reset position coordinates to baseline seed
                node["Qy"] = [0, 0]
                node["Qz"] = [0, 0]
            
            # Map the exact C positions directly onto our screen array
            sx, sy = project_iso(node["Qx"], node["Qy"], node["Qz"])
            if 0 <= sx < WIDTH and 0 <= sy < HEIGHT:
                canvas[sy][sx] = f"\033[1;36m{node['sym']}\033[0m" # Cyan visual nodes
                
        # Draw the frame layout to stdout
        output_buffer = ["\033[H"] # Return terminal cursor to top-left position
        output_buffer.append(f"=== ULDA Topological Network Tracker | Tick: {tick:04d} ===\n")
        for row in canvas:
            output_buffer.append("".join(row) + "\n")
            
        sys.stdout.write("".join(output_buffer))
        sys.stdout.flush()
        
        tick += 1
        time.sleep(0.08) # Match processing step rate to visibility frame intervals

except KeyboardInterrupt:
    print("\n[Simulation Detached] Terminal display buffer cleared.")
