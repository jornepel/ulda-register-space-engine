def layer_drop(self):
    # Stage 1 — Interface 11 phase-lock (Directe parallelle array subtractie)
    v = self.a0
    v = cp.where(v >= 11, v - 11, v)

    # Stage 2 — Layer-drop (FIXED: WAARDE-shift via bit-slices, niet register-shift)
    w_60_3 = v
    w_60_2 = w_60_3 >> 8
    w_60_1 = w_60_2 >> 8
    w_60_0 = w_60_1 >> 8

    # Stage 3 — Feedback (Bitmask van alle vier lagen)
    feedback = (w_60_3 & 0xFF) + (w_60_2 & 0xFF) + (w_60_1 & 0xFF) + (w_60_0 & 0xFF)
    
    # Stage 4 — Omitted 6 (FIXED: Directe parallelle array subtractie)
    feedback = cp.where(feedback >= self.OMITTED_6, feedback - self.OMITTED_6, feedback)

    # Stage 5 — Mod 72 (FIXED: Volledig gevectoriseerde subtractie-ladder)
    mod72 = feedback
    mod72 = cp.where(mod72 >= 576, mod72 - 576, mod72)
    mod72 = cp.where(mod72 >= 288, mod72 - 288, mod72)
    mod72 = cp.where(mod72 >= 144, mod72 - 144, mod72)
    mod72 = cp.where(mod72 >= 72,  mod72 - 72,  mod72)

    # Commit direct naar de klassesecties
    self.a0 = w_60_3
    self.a1 = w_60_2
    self.a2 = w_60_1
    self.a3 = w_60_0
    
    return feedback
