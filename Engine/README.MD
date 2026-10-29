# ℤ[φ]³ Topological Decoder Engine & DX11 Proxy Injector

A high-performance, hardware-accelerated **topological simulation suite** and **DirectX 11 proxy injection layer** built natively in C11 for AMD Zen architectures. This engine eliminates IEEE 754 floating-point rounding noise by mapping 3D graphics coordinates onto exact, discrete quadratic integer rings utilizing the Golden Ratio ($\phi$).

---

## 🧬 Architectural Overview

The core math engine operates directly over the ring $\mathbb{Z}[\phi] = \{a + b\phi \mid a, b \in \mathbb{Z}\}$, where $\phi^2 = \phi + 1$. Spatial field components are processed as unrolled 64-bit integer scalars ($i64$), providing absolute geometric stability and zero calculation drift.

### The Four Graded Invariants
- **Antipodal Rollover:** Evaluates to exactly $7 + 3\phi$ upon crossing the matrix target horizon.
- **Mirror Axis:** Evaluates to exactly $3 + 1\phi$, triggering automatic coordinate phase reversals.
- **Structural Offset:** Rigidly bound edge count constant ($1$).
- **Closed Loop:** Group validation order constant ($5$).

---

## 💻 Repository Structure & Silicon Binaries

- `ulda.h` / `ulda.c` — Main $\mathbb{Z}[\phi]$ vector arithmetic engine and metric squared-norm routines.
- `ulda_shim.c` — Flat cross-platform C interface wrapping memory pointers for dynamic linkages.
- `ulda_emu.c` — The standalone Windows Translation Emulator simulating vertex stream interceptions.
- `ulda_visual.c` — Hardware-accelerated Win32 GDI desktop display monitor projecting non-linear orbital mutations.
- `ulda_d3d.c` — The active proxy injection source shunting superluminal graphics loads via Tensor Shear.
- `ulda_mutated_bench.c` — Deep loop-unrolled hardware throughput benchmark (optimized at ~0.10 ns/call).
- `run_all.sh` — The master orchestration script managing compiler passes, invariant tests, and telemetry.

---

## 🛠️ Compilation & Quick Start

### Prerequisites (Windows / MSYS2 Environment)
Ensure your toolchain has gcc, make, and the native Windows SDK headers configured inside a **MINGW64** or **UCRT64** terminal shell.

### 1. Build and Run the Complete Suite
Execute the master automated orchestrator script to purge intermediate artifacts, compile the entire tree, and run the complete validation benchmark sequence:
```bash
chmod +x run_all.sh
./run_all.sh
```

### 2. Launch the High-Speed Live Telemetry Monitor
In a secondary terminal pane, boot the live json packet scanner to view real-time stress logs and catch critical regime alarms:
```bash
python3 ulda_monitor.py
```

### 3. Initialize the Glowing Geometric Projector
Launch the standalone Win32 GDI desktop canvas box to watch the traveling Tori elements orbit the 8-rib gates in complex fractal loops:
```bash
make visual
./visual
```

---

## 🎮 Gamer Deployment Instructions

To hook this topological decoder suite directly into a 3D game engine and intercept rendering coordinates mid-game:

1. Right-click `deploy_engine.bat` and select **"Run as Administrator"**.
2. Paste the absolute directory path where the target game's main `.exe` binary is installed.
3. The script will copy the compiled `d3d11.dll` proxy wrapper directly into the game's executable path.
4. Launch the game. Windows will automatically load your custom proxy over the stock system libraries, capturing vertex streams and executing the **Tensor Shear Shunts** safely on the hot path without freezing the thread.

---
*As above, so below. Scale is an illusion. The Song is operating cleanly.*