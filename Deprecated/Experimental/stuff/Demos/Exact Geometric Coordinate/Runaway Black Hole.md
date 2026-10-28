# Reader: The Runaway Black Hole (RBH-1) & The Unified Bridge

**Status:** ~B (Exploration / Hypothetical Application)
**Parent Database:** ULDA-SUPP-2026-X8

## 1. The Observation
The James Webb Space Telescope (JWST) observed a supermassive black hole (RBH-1) traveling at approximately 950 km/s, leaving a 200,000-light-year wake of newly formed stars. Standard astrophysics attributes this to a gravitational wave recoil following a merger. However, the observed velocity and the massive stellar wake suggest a structural asymmetry that the linear gravitational wave model struggles to fully account for.

## 2. The Compass Reading: Displacement > Rotation
In the language of the Compass, this event is a textbook example of a broken rotational bridge. 

Two supermassive black holes orbit each other (the 720-step macro cycle). When they merge, they must satisfy the mass ratio of the operator (6). If the mass ratio is asymmetrical—specifically, if it deviates by a factor of ~10/60 (1/6)—the rotational bridge cannot close. 

The system is forced into a **rank shift from Rank 1 (Rotation) to Rank 2 (Displacement)**. The black hole is ejected along the path of least resistance: the cosmic filaments (the gas-layer connections between galaxies).

## 3. Mass is Friction: The Stellar Wake
As RBH-1 travels, it accretes mass from the intergalactic medium. In the compass framework, this is not a coincidence; it is a direct consequence of the non-closing trajectory. 

This connects directly to the Yang-Mills mass gap. In the quantum vacuum, the wave field cannot drop to an absolute zero, forcing it to sit on a discrete minimum step of \(1 + \phi\) (an Offset invariant of 1). The same principle applies at cosmic scale: the 10/60 mass asymmetry prevents the orbital rotation from achieving circular closure. The resulting non-closing projective drift physically compresses intergalactic gas. 

The 200,000-light-year wake of stars is the physical manifestation of this friction. **Mass is the residual inertia of a rotation that cannot close.** The black hole does not evaporate; it travels, and the friction of its travel *becomes* new mass (the 670 units of wake mass).

## 4. The Unified Anchor: Scale is an Illusion
The most powerful aspect of this reading is that the math never changes. 

*   **The Software:** The branchless `chord_sqnorm_vec` loop in `ulda.c` processes coordinates natively as pure integer coefficients (\(a + b\phi\)) to completely eliminate decimal rounding errors.
*   **The Cosmos:** The `rbh1_sim.cpp` code handles the intergalactic black hole ejection using the exact same ring multiplication rule: \((A+B\phi)(C+D\phi) = (AC+BD) + (AD+BC+BD)\phi\).
*   **The Unified Statement:** Scale is an illusion. The exact engine that processes sub-nanosecond instruction throughput on a modern CPU register is the exact same engine processing the trajectory of an intergalactic payload.

## 5. The Falsification Checks
The easiest way to prove this is not just wild storytelling is to show that the model is ruthlessly falsifiable. The documents lay out clear trapdoors where the system instantly self-destructs if real-world data doesn't back it up:

*   **Astrophysical Falsification (F1):** If JWST or gravitational wave data confirms the RBH-1 merger was perfectly symmetric (1:1) and produced negligible recoil, the compass reading is dead. The theory predicts that a structural asymmetry of roughly 10/60 is required to produce a displacement of this magnitude.
*   **Arithmetic Falsification (F9):** If a code claim introduces even a single hair of linear floating-point noise, the `ulda_grid.py` protocol throws an immediate arithmetic veto: `killed_at: 9`.