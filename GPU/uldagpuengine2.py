"""
ULDA GPU Engine — The LUM on the GPU (Optimized with Bitshifts)
================================================================
License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).

The LUM on the GPU. No division. No floating-point. High-speed bitshifts.
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
    # LUM MODULO — EXPONENTIAL BITSHIFT (HIGH SPEED, NO DIVISION)
    # ────────────────────────────────────────────────────────────
    def _lum_mod(self, arr, divisor):
        if divisor <= 0:
            return cp.zeros_like(arr)
            
        value = arr.copy()
        
        # Maak een kopie van de divisor op de GPU voor de bitshift-ladder
        temp_divisor = cp.full_like(value, divisor, dtype=cp.int64)
        shift = 0

        # Stap 1: Shift de divisor naar links totdat hij vlak onder het maximum van de array zit
        while True:
            # Voorkom overflow in 64-bit integers bij het links-shiften
            next_shift = temp_divisor << 1
            mask = (value >= next_shift) & (next_shift > 0)
            if not mask.any():
                break
            # Shift alleen de elementen die nog groter zijn dan de vermenigvuldigde divisor
            temp_divisor = cp.where(mask, next_shift, temp_divisor)
            shift += 1

        # Stap 2: Trek exponentieel af en shift met bitwise-operaties terug naar rechts
        while shift >= 0:
            mask = value >= temp_divisor
            value = cp.where(mask, value - temp_divisor, value)
            temp_divisor >>= 1 # De cruciale Mesopotamische bitshift!
            shift -= 1

        return value

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

    print("=" * 60)
    print("RUNNING OPTIMIZED BITSHIFT GPU_LUM")
    print("=" * 60)
    print("Before LUM:")
    print("  a0 =", cp.asnumpy(lum.a0))

    lum.lum_cycle()

    print("\nAfter LUM (Optimized Phase Lock):")
    print("  a0 =", cp.asnumpy(lum.a0))
    print("  a1 =", cp.asnumpy(lum.a1))
    print("  a2 =", cp.asnumpy(lum.a2))
    print("  total =", cp.asnumpy(lum.total_amplitude())[0])
