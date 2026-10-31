#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
==============================================================================
ulda_monitor.py — Real-Time JSON Telemetry Stream Scanner & Regime Monitor
Listens for state updates and triggers automated boundary warnings.
==============================================================================
"""

import sys
import json
import time
import socket

HOST = '127.0.0.1'
PORT = 60000

def parse_telemetry_packet(data_string):
    """Safely decodes incoming structural logs from the core math loop."""
    try:
        packet = json.loads(data_string)
        
        # Pull structural fields directly
        timestamp = packet.get("time_tick", 0)
        vector_str = packet.get("coordinate_vec", "(0+0φ, 0+0φ, 0+0φ)")
        norm_a = packet.get("norm_a", 0)
        norm_b = packet.get("norm_b", 0)
        
        print(f"[{timestamp:08d}] Vector Coordinates: {vector_str}")
        print(f"           Metric Field Norm : {norm_a} + {norm_b}φ")
        
        # Automated Boundary Inspection Checks
        if norm_a >= 7:
            print("\033[91m[ HORIZON EXCEEDED ALARM ] Vector passed the Antipodal Barrier!\033[0m")
        elif norm_a == 3 and norm_b == 1:
            print("\033[94m[ STATE EVENT CHECK ] Vector reflecting perfectly across Mirror Plane.\033[0m")
        
        print("-" * 70)
        sys.stdout.flush() # Force Windows terminal buffers to display immediately
        
    except json.JSONDecodeError:
        print(f"\033[93m[ TELEMETRY MISMATCH ] Raw Stream Payload: {data_string}\033[0m")
        sys.stdout.flush()

def start_monitor():
    print("====================================================================")
    print(" INITIALIZING LIVE TELEMETRY MATRIX MONITOR SCANNER")
    print(f" Listening on local port socket interface: {HOST}:{PORT}")
    print("====================================================================\n")
    sys.stdout.flush()

    # Set up a simple, lightweight UDP listener loop with immediate reuse options
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        try:
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind((HOST, PORT))
            
            while True:
                data, addr = s.recvfrom(4096)
                clean_payload = data.decode('utf-8').strip()
                parse_telemetry_packet(clean_payload)
        except KeyboardInterrupt:
            print("\n[ STATUS ] Shutting down telemetry matrix stream scanner loop safely.")
            sys.stdout.flush()
        except Exception as e:
            print(f"[ EXCEPTION ALARM ] Network socket error encountered: {e}")
            sys.stdout.flush()

if __name__ == "__main__":
    start_monitor()
