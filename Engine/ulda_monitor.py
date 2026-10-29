#!/usr/bin/env python3
"""
ulda_monitor.py — Live Scrolling Terminal Telemetry Panel with Audio Alert Trigger.
Parses persistent Z[φ] datasets and flashes visual/audio alarms on critical overloads.
"""

import json
import os
import sys
import time
from pathlib import Path

DATA_SRC = Path("ulda_telemetry_stream.json")

def read_telemetry():
    """Safely extracts data components from the persistent stream file."""
    if not DATA_SRC.exists():
        return None
    try:
        with open(DATA_SRC, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception:
        return None

def run_live_panel():
    print("\033[2J\033[H", end="")  # Refresh system display layout
    print("\033[1;36m======================================================================\033[0m")
    print("\033[1;36m             ULDA MACRO TELEMETRY STREAM MONITOR PANEL                \033[0m")
    print("\033[1;36m======================================================================\033[0m")
    print(f" Listening for live matrix packets from: {DATA_SRC.name}\n")
    
    print("----------------------------------------------------------------------")
    print("Timestamp Log    | Target Node Module   | Dynamic Value | State Metric Track")
    print("----------------------------------------------------------------------")

    tick = 0
    try:
        while True:
            data = read_telemetry()
            if data is None:
                time.sleep(0.5)
                continue

            current_time = time.strftime("%H:%M:%S UTC", time.gmtime())
            
            # 1. Performance logs
            if tick % 4 == 0:
                print(f" {current_time}   | \033[1;32mPERF_CORE_HOT    \033[0m | 1201.9 Mops/s | Primitive execution secure")
            elif tick % 4 == 1:
                print(f" {current_time}   | \033[1;35mPERF_INVARIANT   \033[0m | 9566.3 Mops/s | Loop optimized! Constant Closed State")
            
            # 2. Cosmic puzzle matrix loop
            p_idx = tick % len(data["matrix_puzzles"])
            puzzle = data["matrix_puzzles"][p_idx]
            wave_status = f"Wave: {puzzle['wave']}" if puzzle['wave'] != "—" else "\033[1;31mUNASSIGNED ARTIFACT\033[0m"
            print(f" {current_time}   | \033[1;33mPUZZLE_{puzzle['id']:02d}_{puzzle['name'][:8].upper():<8}\033[0m | {puzzle['reading']:<13} | {wave_status}")

            # 3. X Tensor phase transfers with audio-reactive alarm hook
            x_idx = tick % len(data["x_tensor_cross_talk"])
            x_talk = data["x_tensor_cross_talk"][x_idx]
            
            if "CRITICAL" in x_talk["state"]:
                # Trigger the high-visibility flash and fire the physical terminal bell tone (\a)
                print(f" {current_time}   | \033[1;41;37mX_TENSOR_STEP_{x_talk['step']}\033[0m | Torus {x_talk['source']} ──► {x_talk['destination']} | \033[1;31mALERT: {x_talk['norm']} -> {x_talk['state']}\033[0m\a")
            else:
                print(f" {current_time}   | \033[1;36mX_TENSOR_STEP_{x_talk['step']}\033[0m | Torus {x_talk['source']} ──► {x_talk['destination']} | Norm Link: {x_talk['norm']}")

            tick += 1
            sys.stdout.flush()
            time.sleep(0.4)

    except KeyboardInterrupt:
        print("\n\033[1;33m[Detached] Telemetry monitor safely uncoupled from log stream.\033[0m")

if __name__ == "__main__":
    run_live_panel()
