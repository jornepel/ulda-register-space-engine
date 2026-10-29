"""
ulda_monitor.py — Live Microtonal Chord Telemetry & Scrolling Terminal Monitor.
Translates exact Z[φ] matrix data steps into active musical voice structures.
"""

import json
import os
import sys
import time
import math
from pathlib import Path

DATA_SRC = Path("ulda_telemetry_stream.json")
BASE_WHEEL = 60.0  # Core engine fundamental tracking clock (n=1)

def read_telemetry():
    if not DATA_SRC.exists():
        return None
    try:
        with open(DATA_SRC, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception:
        return None

def calculate_microtonal_chord(base60_val, shift_val):
    """Calculates exact equal-tempered microtonal triad chord frequencies."""
    # 24-tone spectrum division tracking step rule
    step_ratio = 2.0 ** (1.0 / 24.0)
    
    # Root voice derived from the base60 phase index
    root_step = (base60_val % 24)
    freq_root = BASE_WHEEL * (step_ratio ** root_step)
    
    # Major Third voice driven by the pentatonic folding key (5 steps up)
    third_step = (root_step + 5 + abs(shift_val)) % 24
    freq_third = BASE_WHEEL * (step_ratio ** third_step)
    
    # Perfect Fifth voice driven by the rotational vector key (7 steps up)
    fifth_step = (root_step + 7) % 24
    freq_fifth = BASE_WHEEL * (step_ratio ** fifth_step)
    
    return freq_root, freq_third, freq_fifth

def run_live_panel():
    print("\033[2J\033[H", end="")
    print("\033[1;36m======================================================================\033[0m")
    print("\033[1;36m             ULDA MICROTONAL CHORD TELEMETRY TRACKER PANEL            \033[0m")
    print("\033[1;36m======================================================================\033[0m")
    print(f" Listening for live matrix packets from: {DATA_SRC.name}\n")
    
    print("--------------------------------------------------------------------------------")
    print("Timestamp Log | Active Puzzle Node | Wave | Triad Chord Frequencies (Root/3rd/5th)")
    print("--------------------------------------------------------------------------------")

    tick = 0
    try:
        while True:
            data = read_telemetry()
            if data is None:
                time.sleep(0.5)
                continue

            current_time = time.strftime("%H:%M:%S UTC", time.gmtime())
            
            # Fetch active puzzle dataset from our expanded properties matrix
            p_idx = tick % len(data["matrix_puzzles"])
            p = data["matrix_puzzles"][p_idx]
            
            # Calculate the live acoustic chord variables
            f_root, f_third, f_fifth = calculate_microtonal_chord(p["base60"], p["shift"])
            
            # Formatting symbols for the unassigned boundary artifacts
            is_artifact = p["wave"] == "—"
            wave_str = f"W_{p['wave']}" if not is_artifact else "\033[1;31mARTIFACT\033[0m"
            color = "\033[1;31m" if is_artifact else "\033[1;32m"
            
            # Render the dynamic scrolling chord telemetry data
            chord_str = f"Root: {f_root:.2f}Hz | 3rd: {f_third:.2f}Hz | 5th: {f_fifth:.2f}Hz"
            print(f" {current_time} | {color}{p['name'][:14]:<14}\033[0m | {wave_str:<8} | \033[1;33m{chord_str}\033[0m")
            
            # Overload event check triggered via the X Tensor matrix data
            x_idx = tick % len(data["x_tensor_cross_talk"])
            x_talk = data["x_tensor_cross_talk"][x_idx]
            if "CRITICAL" in x_talk["state"] and tick % 3 == 0:
                print(f" {current_time} | \033[1;41;37mX_TENSOR_ALERT\033[0m | SHUNT    | \033[1;31mDisplacement Overload Vector: {x_talk['norm']}\033[0m\a")

            tick += 1
            sys.stdout.flush()
            time.sleep(0.5)

    except KeyboardInterrupt:
        print("\n\033[1;33m[Detached] Telemetry monitor safely uncoupled from log stream.\033[0m")

if __name__ == "__main__":
    run_live_panel()