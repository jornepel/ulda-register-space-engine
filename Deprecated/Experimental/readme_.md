## Building

### Run the test (visible)

```bash
make test

This compiles ulda.c and test.c together and runs the test harness.
You will see the gate, the lock, the operator, the conversion, the carry,
and the checksum.
Build the bare-metal object (no OS)
bash

make bare

This compiles ulda.c alone with -nostdlib -ffreestanding.
No standard library. No OS. Pure engine.
Clean
bash

make clean

text


---

**Dus nu:**
- **`ulda.c`** = de engine (bare metal, puur)
- **`test.c`** = de test (met `printf`, zodat je het **ziet**)
- **`Makefile`** = `make test` en je ziet het werken

**En dan:**
- Typ `make test`
- En dan zie je:

ULDA-X28 — Base-60 2x5 Engine Test
==================================

The gate: 11 (expected 11)
The lock (360): 5 (expected 5)
Operator (137): 5 (expected 5)
Convert (36620): sar=0 gesu=10 ges=10 dis=20
(expected sar=0 gesu=10 ges=10 dis=20)
Carry (59+1): dis=0 ges=1
(expected dis=0 ges=1)

Checksum: 62 (expected 62 = 60 + 2)
