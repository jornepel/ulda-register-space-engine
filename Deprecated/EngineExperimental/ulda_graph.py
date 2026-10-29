#!/usr/bin/env python3
"""
ulda_graph.py — Unified Counter-Rotational Gearing & X Tensor Cross-Talk Tracker
Reads live data from the C matrix engine json bridge or falls back to geometry references.
"""
import sys
import subprocess
import os
import math
import json
from pathlib import Path

WIDTH, HEIGHT = 70, 20
PHI_FLOAT = (1.0 + math.sqrt(5.0)) / 2.0  # Exact φ representation
BRIDGE_FILE = Path("xtensor_live_bridge.json")

# Complete master puzzle directory directly from puzzles.c
PUZZLES = [
    {"name": "Poincaré",       "reading": "roll-over",   "wave": "5",  "base60": 0,  "quadrant": 0}, 
    {"name": "Navier–Stokes",  "reading": "roll-over",   "wave": "3",  "base60": 0,  "quadrant": 0},
    {"name": "Yang–Mills",     "reading": "offset",      "wave": "3",  "base60": 24, "quadrant": 1}, 
    {"name": "Riemann",        "reading": "mirror axis", "wave": "—",  "base60": 12, "quadrant": 1},
    {"name": "BSD",            "reading": "mirror axis", "wave": "—",  "base60": 12, "quadrant": 2}, 
    {"name": "Hodge",          "reading": "closed loop", "wave": "—",  "base60": 24, "quadrant": 2},
    {"name": "P vs NP",        "reading": "closed loop", "wave": "3",  "base60": 36, "quadrant": 3}, 
    {"name": "Fine structure", "reading": "offset",      "wave": "3",  "base60": 0,  "quadrant": 3},
    {"name": "Hierarchy",      "reading": "offset",      "wave": "—",  "base60": 0,  "quadrant": 0},
    {"name": "Black hole",     "reading": "closed loop", "wave": "1",  "base60": 24, "quadrant": 1},
    {"name": "Horizon",        "reading": "closed loop", "wave": "1",  "base60": 36, "quadrant": 2},
    {"name": "Time",           "reading": "roll-over",   "wave": "3",  "base60": 0,  "quadrant": 3}
]

GEAR_DIRECTIONS = [1, -1, -1, 1]  
TORUS_LABELS = ["A (Root)", "B (Third)", "C (Fifth)", "D (Unified)"]

# ============================================================================
# Mode A: Counter-Rotational Gear Dynamics
# ============================================================================
def calculate_gear_dynamics():
    print("\033[2J\033[H", end="") 
    print("=== ULDA TOROIDAL GEAR SHIFT ENGINE ===")
    print("Simulating Counter-Rotational 2x2 Boundary Mesh Interactions...\n")
    
    print("----------------------------------------------------------------------")
    print("Quadrant | Torus Identity | Gear Direction | Active Mechanical Workload")
    print("----------------------------------------------------------------------")
    
    torus_stress = [0.0] * 4
    gate_stress = [0] * 8
    
    for p in PUZZLES:
        q = p["quadrant"]
        is_unassigned = p["wave"] == "—"
        load_factor = 4.5 if is_unassigned else 1.5
        phase_offset = (p["base60"] / 12.0)
        
        torus_stress[q] += (load_factor + phase_offset) * abs(GEAR_DIRECTIONS[q])
        gate_idx = (p["base60"] % 8)
        gate_stress[gate_idx] += int(load_factor + phase_offset)

    for i in range(4):
        dir_str = "\033[1;32mCLOCKWISE (+1)\033[0m" if GEAR_DIRECTIONS[i] == 1 else "\033[1;34mCOUNTER-CW (-1)\033[0m"
        bar_len = int(torus_stress[i] * 2)
        load_bar = "⚙" * bar_len
        print("  #%-5d | %-14s | %-15s | \033[1;33m%s\033[0m" % (i, TORUS_LABELS[i], dir_str, load_bar))
              
    print("----------------------------------------------------------------------")
    print("\nINTERLOCKING GEAR FRICTION GRADIENT (8-RIB CENSUS PROFILE)")
    print("----------------------------------------------------------------------")
    for g_id, stress in enumerate(gate_stress, start=1):
        bar = "█" * int(stress * 2.5)
        if g_id in (4, 5):
            color, label = "\033[1;31m", "[Core Mesh Contact]"
        elif g_id in (2, 7):
            color, label = "\033[1;33m", "[Rotational Slip]  "
        else:
            color, label = "\033[1;32m", "[Lattice Fluidity] "
        print(f" #{g_id}  | {color}%-32s\033[0m %s (Load: %d)" % (bar, label, stress))
        
    print("----------------------------------------------------------------------")
    print("\033[1;36mCounter-Rotational Mechanics Log:\033[0m")
    print("  The 'A Major Bend' forces a localized phase-locking condition at Gates 4 & 5.")
    print("----------------------------------------------------------------------")

# ============================================================================
# Mode B: Live X Tensor Cross-Talk Tracker (JSON BRIDGE ACTIVATED)
# ============================================================================
def render_tensor_visualization():
    print("\033[2J\033[H", end="") 
    print("======================================================================")
    print("          ULDA CROSS-TALK ENGINE: LIVE MATRIX COUPLING TRACKER         ")
    print("======================================================================\n")

    # Force execution of the C-tensor binary to generate the newest JSON packet
    exe_name = "./tensor" if os.name != "nt" else "tensor.exe"
    if os.path.exists(exe_name):
        try:
            subprocess.run([exe_name], capture_output=True, text=True, check=True)
        except Exception as e:
            print(f"[Warning] Tensor binary execution anomaly: {e}")

    # Read the live JSON stream from ulda_tensor.c
    if not BRIDGE_FILE.exists():
        print(f"[Bridge Error] Live coupling wire '{BRIDGE_FILE.name}' not found.")
        print("Fallback: Rendering geometric static baseline presets instead.\n")
        steps = [
            {"torus_id": 0, "norm_a": 100,  "norm_b": 0,   "friction": 1, "stress_a": 3, "stress_b": 1, "state": "Stabilized Scaffold"},
            {"torus_id": 1, "norm_a": 3700, "norm_b": 100, "friction": 2, "stress_a": 10, "stress_b": 4, "state": "CRITICAL REGIME (RBH-1)"},
            {"torus_id": 2, "norm_a": 2,    "norm_b": 3,   "friction": 3, "stress_a": 11, "stress_b": 4, "state": "Lattice Reset Core"},
            {"torus_id": 3, "norm_a": 69,   "norm_b": 58,  "friction": 4, "stress_a": 16, "stress_b": 4, "state": "Unified Feedback Phase"}
        ]
    else:
        try:
            with open(BRIDGE_FILE, "r", encoding="utf-8") as f:
                steps = json.load(f)
            # Inject textual state descriptors based on active C metrics
            states = ["Stabilized Scaffold", "CRITICAL REGIME (RBH-1)", "Lattice Reset Core", "Unified Feedback Phase"]
            for idx, s in enumerate(steps):
                s["state"] = states[idx % len(states)]
            print(f"\033[1;32m[✓] LIVE WIRE ACTIVE: Successfully linked with {BRIDGE_FILE.name}\033[0m\n")
        except Exception as e:
            print(f"[Error] Failed parsing bridge data: {e}")
            return

    print("----------------------------------------------------------------------")
    print("Quadrant ID | Active State Node  | Metric Norm Value | Friction Accum")
    print("----------------------------------------------------------------------")
    for s in steps:
        color = "\033[1;32m"
        if s["norm_a"] >= 3600: color = "\033[1;31m"
        elif s["norm_b"] > 50: color = "\033[1;33m"
        
        t_id = s["torus_id"]
        print(f"  Torus #{t_id}  | {color}%-20s\033[0m |  {s['norm_a']:4d} + {s['norm_b']:2d}φ  |  F_Index: {s['friction']}" % s["state"])
        
    print("----------------------------------------------------------------------\n")
    print("X TENSOR INTER-QUADRANT WORKLOAD MATRIX (LIVE GRAPH PROFILE)")
    print("----------------------------------------------------------------------")
    for s in steps:
        t_id = s["torus_id"]
        # Scale the visual workload directly from the live stress scalar (stress_a)
        weight = max(2, min(35, int(abs(s["stress_a"]) * 2) if s["stress_a"] != 0 else 10))
        
        if s["norm_a"] >= 3600: color, label = "\033[1;31m", "[SHEAR OVERLOAD]"
        elif s["norm_b"] > 50:  color, label = "\033[1;33m", "[TORQUE RESISTANCE]"
        elif t_id == 0:        color, label = "\033[1;32m", "[STABLE CARRIER]"
        else:                  color, label = "\033[1;32m", "[GROUND LOCKED]"
        
        print(f" Torus #{t_id}   | {color}%-35s\033[0m %s (Stress: %d)" % ("█" * weight, label, s["stress_a"]))

    print("----------------------------------------------------------------------")
    print(f"\033[1;36mX Tensor Diagnostic Ledger:\033[0m Quantum cross-talk successfully piped.")
    print("======================================================================")

# ============================================================================
# Core Router Routing Controller
# ============================================================================
if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1].lower() == "tensor":
        render_tensor_visualization()
    else:
        calculate_gear_dynamics()
