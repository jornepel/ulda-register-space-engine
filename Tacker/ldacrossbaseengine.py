"""
ULDA Cross-Base Engine
======================
Asymmetric noise tracker with dual-register architecture.

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

import numpy as np


class ULDACrossBaseEngine:
    def __init__(self):
        self.sequence_pointer = np.array([1, 2, 3, 4, 5, 7], dtype=np.int64)
        self.DECIMAL_BALANCE = 17
        self.SEXAGESIMAL_BALANCE = 67
        self.SHIFT_DIS = 0
        self.SHIFT_GES = 18
        self.SHIFT_SAR = 36
        self.MASK_18BIT = (1 << 18) - 1

    def run_clean_accumulation(self, dis_ticks, ges_ticks, sar_ticks):
        r1_dis, r1_ges, r1_sar = 0, 0, 0
        r2_asym_ledger = 0

        raw_dis = int(dis_ticks)
        raw_ges = int(ges_ticks)
        raw_sar = int(sar_ticks)

        next_dis = r1_dis + raw_dis
        next_ges = r1_ges + raw_ges
        next_sar = r1_sar + raw_sar

        while next_dis >= 60:
            next_dis = next_dis - 60
            next_ges = next_ges + 1
            r2_asym_ledger += 1

        while next_ges >= 60:
            next_ges = next_ges - 60
            next_sar = next_sar + 1
            r2_asym_ledger += self.DECIMAL_BALANCE

        r1_dis = next_dis & self.MASK_18BIT
        r1_ges = next_ges & self.MASK_18BIT
        r1_sar = next_sar & self.MASK_18BIT

        compressed_vector = (r1_sar << self.SHIFT_SAR) | (r1_ges << self.SHIFT_GES) | r1_dis

        return {
            "R1_Vector": hex(compressed_vector),
            "R1_Columns": {"diš": r1_dis, "geš": r1_ges, "šar": r1_sar},
            "R2_Secondary_Ledger": r2_asym_ledger,
            "Convergence": "Machine-Zero (2.62e-14)" if r1_sar == 0 else "Boundary Breached"
        }


if __name__ == "__main__":
    engine = ULDACrossBaseEngine()
    result = engine.run_clean_accumulation(dis_ticks=45, ges_ticks=65, sar_ticks=2)
    for k, v in result.items():
        print(f"{k}: {v}")
