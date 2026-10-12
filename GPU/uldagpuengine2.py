"""
ULDA GPU Engine — The LUM on the GPU
=====================================
License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).

The LUM on the GPU. No division. Only subtraction.
"""

import cupy as cp


class GPU_LUM:
    RADIX        = 60
    INTERFACE_11 = 11
    OMITTED_6    = 6
    ROTATION_72  = 72
    SHIFT_8      = 8
    BOUNDARY_504 = 504

    def __init__(self, size=1024):
        self.size = size
        # Allocate GPU arrays
        self.a0 = cp.zeros(size, dtype=cp.int64)
        self.a1 = cp.zeros(size, dtype=cp.int64)
        self.a2 = cp.zeros(size, dtype=cp.int64)
        self.a3 = cp.zeros(size, dtype=cp.int64)

    # ────────────────────────────────────────────────────────────
    # OP 01 — LAYER-DROP (>> 8)
    # ────────────────────────────────────────────────────────────
    def layer_drop(self):
        # Capture residual from a0
        residual = self.a0.copy()
        # Shift layers down
        self.a0 = self.a1
        self.a1 = self.a2
        self.a2 = self.a3
        self.a3 = cp.zeros(self.size, dtype=cp.int64)
        # Route residual through the Omitted 6 Operator
        return self._lum_mod(residual, self.OMITTED_6)

    # ────────────────────────────────────────────────────────────
    # LUM MODULO — SUBTRACTION ONLY
    # ────────────────────────────────────────────────────────────
    def _lum_mod(self, arr, divisor):
        tmp = arr.copy()
        # Subtraction loop (vectorized)
        while True:
            mask = tmp >= divisor
            if not mask.any():
                break
            tmp = tmp - (mask.astype(cp.int64) * divisor)
        return tmp

    # ────────────────────────────────────────────────────────────
    # OP 04 — INTERFACE 11 PHASE-LOCK
    # ────────────────────────────────────────────────────────────
    def interface_11(self):
        remainder = self._lum_mod(self.a0, self.INTERFACE_11)
        self.a0 = self.a0 - remainder

    # ────────────────────────────────────────────────────────────
    # OP 03 — 72° ROTATION LOCK
    # ────────────────────────────────────────────────────────────
    def lock_72(self):
        variance = self._lum_mod(self.a0, self.ROTATION_72)
        # Apply correction torque
        correction = cp.where(variance == 0, 0, self.ROTATION_72 - variance)
        self.a0 = self.a0 + correction

    # ────────────────────────────────────────────────────────────
    # OP 05 — 504 BOUNDARY CHECK
    # ────────────────────────────────────────────────────────────
    def boundary_check(self):
        breach = self.a0 > self.BOUNDARY_504
        self.a0 = cp.where(breach, self.a0 - self.BOUNDARY_504, self.a0)
        return breach

    # ────────────────────────────────────────────────────────────
    # FULL LUM CYCLE
    # ────────────────────────────────────────────────────────────
    def lum_cycle(self):
        self.interface_11()
        self.layer_drop()
        self.lock_72()
        return self.boundary_check()

    # ────────────────────────────────────────────────────────────
    # READOUT
    # ────────────────────────────────────────────────────────────
    def total_amplitude(self):
        return (self.a0
                + self.a1 * self.RADIX
                + self.a2 * self.RADIX ** 2
                + self.a3 * self.RADIX ** 3)


if __name__ == "__main__":
    lum = GPU_LUM(size=16)
    # Inject 12,500 on the first node
    lum.a0[0] = 12500

    print("Before LUM:")
    print("  a0 =", cp.asnumpy(lum.a0))

    lum.lum_cycle()

    print("After LUM:")
    print("  a0 =", cp.asnumpy(lum.a0))
    print("  a1 =", cp.asnumpy(lum.a1))
    print("  a2 =", cp.asnumpy(lum.a2))
    print("  total =", cp.asnumpy(lum.total_amplitude())[0])
