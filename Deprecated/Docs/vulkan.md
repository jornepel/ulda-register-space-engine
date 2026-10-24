markdown

# ULDA Vulkan — The LUM on Any GPU

**Document Reference:** ULDA-VULKAN-2026-X27
**License:** AGPL-3.0
**Contact:** JornePel@gmail.com
**Dedicated to:** Terrence Andrew Davis (1969–2018)

---

## What this is

A Vulkan compute shader that runs the LUM on any Vulkan-capable GPU.

No CUDA. No HIP. No vendor lock-in. Vulkan runs on:

- NVIDIA
- AMD
- Intel
- Qualcomm
- ARM
- And mobile GPUs

---

## The shader

The LUM is implemented in GLSL (`ulda_lum.comp`).

It executes:

1. Interface 11 phase-lock
2. Layer-Drop (>> 8)
3. Residual routing through the Omitted 6 Operator
4. 72° rotation lock
5. 504 boundary check

No division. Only subtraction.

---

## How to build

**1. Compile the shader to SPIR-V:**

```bash
glslangValidator -V gpu/ulda_lum.comp -o gpu/ulda_lum.spv

2. Install the Python Vulkan bindings:
bash

pip install vulkan

3. Run the host:
bash

python gpu/ulda_vulkan.py

Why Vulkan
API	Vendor	Bare-metal?	Open source?
CUDA	NVIDIA only	Almost	No
HIP	AMD only	Almost	Yes
PTX / SASS	Vendor	Yes	No
Vulkan	All	Almost	Yes

Vulkan is the only GPU API that runs on every vendor and is open source.
The constants
Constant	Value	Meaning
RADIX	60	6 × 10
INTERFACE_11	11	22 / 2
OMITTED_6	6	the operator
ROTATION_72	72	360 / 5
SHIFT_8	8	2³
BOUNDARY_504	504	7 × 72
The full pipeline
text

[ Host: allocate buffers on GPU ]
               │
               ▼
[ Upload a0, a1, a2, a3 to GPU ]
               │
               ▼
[ Dispatch compute shader (1024 nodes, 256 local size) ]
               │
               ▼
[ Shader runs the LUM on every node in parallel ]
               │
               ▼
[ Download results to CPU ]
               │
               ▼
[ Verify 12,500 → [3, 28, 20] on the Base-60 wheel ]

