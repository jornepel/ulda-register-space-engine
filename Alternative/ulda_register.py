"""
ULDA Cross-Base Arithmetic Engine — Python Reference (Optimized & Protected)
=============================================================================
Bit-packed 64-bit implementation of the dual-register sexagesimal carry logic.
Eliminates bit-bleeding channel corruption and accelerates modulo resolution.

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

import numpy as np


class AdvancedCrossBaseRegister64:
    SHIFT_DIS = 0
    SHIFT_GES = 18
    SHIFT_SAR = 36
    MASK_CELL = 0x3FFFF  # Exact 18-bit bitmask

    def __init__(self, raw_int64=0):
        self.data = np.int64(raw_int64)

    @classmethod
    def encode(cls, dis, ges, sar):
        reg = (np.int64(dis & cls.MASK_CELL) << cls.SHIFT_DIS) | \
              (np.int64(ges & cls.MASK_CELL) << cls.SHIFT_GES) | \
              (np.int64(sar & cls.MASK_CELL) << cls.SHIFT_SAR)
        return cls(reg)

    def decode_columns(self):
        dis = int((self.data >> self.SHIFT_DIS) & self.MASK_CELL)
        ges = int((self.data >> self.SHIFT_GES) & self.MASK_CELL)
        sar = int((self.data >> self.SHIFT_SAR) & self.MASK_CELL)
        return dis, ges, sar

    # ─────────────────────────────────────────────────────────────────────
    # LOSSLESS EXPONENTIAL MODULO ENGINE (LOGARITHMIC INT THROUGHPUT)
    # ─────────────────────────────────────────────────────────────────────
    def _bitshift_mod_carry(self, value: int, divisor: int) -> tuple[int, int]:
        if value < divisor:
            return value, 0
        carry_count = 0
        temp_divisor = divisor
        shift = 0
        while value >= (temp_divisor << 1):
            temp_divisor <<= 1
            shift += 1
        while shift >= 0:
            if value >= temp_divisor:
                value -= temp_divisor
                carry_count += (1 << shift)
            temp_divisor >>= 1
            shift -= 1
        return value, carry_count

    def hardware_normalize(self):
        """Resolves column carries in logarithmic time using bitwise shifts."""
        dis, ges, sar = self.decode_columns()
        
        # Fast exponential bitshift resolution instead of slow while-loops
        dis, dis_carries = self._bitshift_mod_carry(dis, 60)
        ges += dis_carries
        
        ges, ges_carries = self._bitshift_mod_carry(ges, 60)
        sar += ges_carries
        
        self.data = self.encode(dis, ges, sar).data

    def inject_scaled_fault(self, other_reg, count, channel_weight):
        """
        Injects a scaled pulse safely. 
        FIXED: Decodes and isolates columns first to prevent cross-channel bit corruption.
        """
        # Extract columns of incoming injection payload
        o_dis, o_ges, o_sar = other_reg.decode_columns()
        scalar = int(count * channel_weight)
        
        # Isolate and scale inputs cleanly
        add_dis = o_dis * scalar
        add_ges = o_ges * scalar
        add_sar = o_sar * scalar
        
        # Decode current master state
        dis, ges, sar = self.decode_columns()
        
        # Aggregate raw values cleanly before encoding back into register
        return AdvancedCrossBaseRegister64.encode(dis + add_dis, ges + add_ges, sar + add_sar)

    def to_decimal_float(self):
        dis, ges, sar = self.decode_columns()
        return dis / (60**0) + ges / (60**1) + sar / (60**2)

    @property
    def state_breached(self):
        _, _, sar = self.decode_columns()
        return sar > 0

    @property
    def state_preserved(self):
        _, _, sar = self.decode_columns()
        return sar == 0


if __name__ == "__main__":
    print("=" * 60)
    print("INITIALIZING TEST RUN ON ADVANCED CROSS-BASE REGISTER 64")
    print("=" * 60)
    reg = AdvancedCrossBaseRegister64()
    
    # Inject 60 iterative raw pulses safely into the dis register layer
    for _ in range(60):
        reg = reg.inject_scaled_fault(
            AdvancedCrossBaseRegister64.encode(1, 0, 0), 1, 1
        )
        
    print("Before hardware normalization:", reg.decode_columns())
    reg.hardware_normalize()
    print("After hardware normalization: ", reg.decode_columns())
    print("Decimal evaluation expression: ", reg.to_decimal_float())
