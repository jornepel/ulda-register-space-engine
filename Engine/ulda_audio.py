"""
ulda_audio.py — Live 3D Topological Acoustic Wave Engine.
Translates discrete Z[phi] vector updates into real-time microtonal audio frequencies.
"""
import os
import sys
import ctypes
import math
import array
import pyaudio

# 1. Dynamically identify and load the Makefile's shared library output
if sys.platform == "darwin":
    lib_name = "libulda.dylib"
elif sys.platform == "win32" or os.name == "nt":
    lib_name = "libulda.dll"  # Match your compiled Windows NT asset name
else:
    lib_name = "libulda.so"

lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), lib_name))

if not os.path.exists(lib_path):
    print(f"[Error] Build the shared library first using './run_all.sh' or 'make lib'")
    sys.exit(1)

ulda = ctypes.CDLL(lib_path)

# 2. Set up the exact argument types for your flat C interface
ulda.chord_sqnorm_flat.argtypes = [
    ctypes.c_longlong, ctypes.c_longlong,  # Ox
    ctypes.c_longlong, ctypes.c_longlong,  # Oy
    ctypes.c_longlong, ctypes.c_longlong,  # Oz
    ctypes.c_longlong, ctypes.c_longlong,  # Qx
    ctypes.c_longlong, ctypes.c_longlong,  # Qy
    ctypes.c_longlong, ctypes.c_longlong,  # Qz
    ctypes.POINTER(ctypes.c_longlong),     # out_a
    ctypes.POINTER(ctypes.c_longlong)      # out_b
]
ulda.chord_sqnorm_flat.restype = None

# 3. Audio hardware configuration (Tuned to the 60Hz macro engine rules)
SAMPLE_RATE = 44100
CHUNK_SIZE = 1024
BASE_WHEEL = 60.0  # Ground fundamental tone (n=1)

p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16,
                channels=1,
                rate=SAMPLE_RATE,
                output=True,
                frames_per_buffer=CHUNK_SIZE)

# 4. Workaround: Populated with exact flat integers to satisfy python's dict syntax
positions = [
    # Torus A: Anchored directly on the Invariant Mirror Plane chord
    {"O": [0, 0, 0, 0, 0, 0], "Q": [0, 0, -1, 1, 0, 1], "gear": 1,  "sym": "A"},
    # Torus B: Anchored directly on the Invariant Rollover Antipodal chord
    {"O": [0, 0, 0, 0, 0, 0], "Q": [-1, 0, -1, 0, -1, 0], "gear": -1, "sym": "B"},
    # Torus C: Parallel Counter-Rotational Copy of the Mirror State
    {"O": [0, 0, 0, 0, 0, 0], "Q": [0, 0, -1, 1, 0, 1], "gear": -1, "sym": "C"},
    # Torus D: Parallel Counter-Rotational Copy of the Rollover State
    {"O": [0, 0, 0, 0, 0, 0], "Q": [-1, 0, -1, 0, -1, 0], "gear": 1,  "sym": "D"}
]

print("[Topological Engine Streaming] Sound active. Press Ctrl+C to stop.")

phase = 0.0
out_a = ctypes.c_longlong(0)
out_b = ctypes.c_longlong(0)

try:
    while True:
        # Fixed list multiplication for initialization
        audio_buffer = array.array('h', [0] * CHUNK_SIZE)
        
        for sample_idx in range(CHUNK_SIZE):
            mixed_wave = 0.0
            
            for p_node in positions:
                # Drive linear coordinate elements precisely
                p_node["Q"][0] += p_node["gear"]
                p_node["Q"][3] += p_node["gear"]
                
                # Execute the exact flat C shim calculation passing individual elements
                ulda.chord_sqnorm_flat(
                    p_node["O"][0], p_node["O"][1], p_node["O"][2], p_node["O"][3], p_node["O"][4], p_node["O"][5],
                    p_node["Q"][0], p_node["Q"][1], p_node["Q"][2], p_node["Q"][3], p_node["Q"][4], p_node["Q"][5],
                    ctypes.byref(out_a), ctypes.byref(out_b)
                )
                
                # Mirror Plane Boundary (3 + 1φ) triggers phase reversal
                if out_a.value == 3 and out_b.value == 1:
                    p_node["gear"] *= -1
                    
                # Antipodal Rollover Boundary (7 + 3φ) triggers rank collapse
                if out_a.value == 7 and out_b.value == 3:
                    p_node["Q"] = [0, 0, -1, 1, 0, 1]  # Reset cleanly to safe horizon seed
                
                # Synthesize the exact microtonal frequency derived from the clean C scalar
                freq_scale = BASE_WHEEL * (1.0 + (abs(p_node["Q"][0]) % 12) / 12.0)
                mixed_wave += math.sin(2.0 * math.pi * freq_scale * (phase / SAMPLE_RATE))
                
            mixed_wave /= 4.0  # Prevent digital clipping across the 4 combined streams
            audio_buffer[sample_idx] = int(mixed_wave * 32767)
            phase += 1.0
            
        stream.write(audio_buffer.tobytes())

except KeyboardInterrupt:
    print("\n[Shutting Down] Engine safely detached.")
    stream.stop_stream()
    stream.close()
    p.terminate()
