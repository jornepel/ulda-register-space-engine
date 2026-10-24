"""
ULDA Cross-Base Arithmetic Engine — Python Reference
=====================================================
Bit-packed 64-bit implementation of the dual-register
sexagesimal carry logic.

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

import numpy as np


class AdvancedCrossBaseRegister64:
    SHIFT_DIS = 0
    SHIFT_GES = 18
    SHIFT_SAR = 36
    MASK_CELL = 0x3FFFF

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

    def hardware_normalize(self):
        dis, ges, sar = self.decode_columns()
        while dis >= 60:
            dis -= 60
            ges += 1
        while ges >= 60:
            ges -= 60
            sar += 1
        self.data = self.encode(dis, ges, sar).data

    def inject_scaled_fault(self, other_reg, count, channel_weight):
        scaled_addition = other_reg.data * np.int64(count * channel_weight)
        return AdvancedCrossBaseRegister64(self.data + scaled_addition)

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
    reg = AdvancedCrossBaseRegister64()
    for _ in range(60):
        reg = reg.inject_scaled_fault(
            AdvancedCrossBaseRegister64.encode(1, 0, 0), 1, 1
        )
    reg.hardware_normalize()
    print("After 60 injections:", reg.decode_columns())
    print("Decimal value:      ", reg.to_decimal_float())
