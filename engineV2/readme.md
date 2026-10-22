markdown

# ULDA Topological Decoder Engine

A base-60 coordinate engine with one operation: the carry.

Integer-only. No floating-point. No zero. Only: knuckles, fingers, macros.

---

## What It Does

The engine represents a number as a coordinate on a hand grid:

knuckles = 1 (1..12)
fingers = 12 (1..5)
macros = 60 (5 x 12)
text


The coordinate is the number of steps per scale. Not the value — the structure.

```c
calculate(1860) = (31, 0, 0)   // 31 macros, 0 fingers, 0 knuckles
calculate(1878) = (31, 1, 6)   // 31 macros, 1 finger, 6 knuckles

And everything is built on the carry:
c

add(a, b)      = carry(a + b)
subtract(a, b) = carry(a - b)
multiply(a, n) = carry(a * n)
divide(a, n)   = carry(a / n)

One tool, many applications.
Why No Zero?

Look at your hand. You have no zeroth finger.

You have 4 fingers with 3 knuckles each, and a thumb. The thumb walks over the knuckles:
text

1, 2, 3  (index)
4, 5, 6  (middle)
7, 8, 9  (ring)
10, 11, 12 (pinky)

When your knuckle-hand is full, you have 12. Then you use your other hand to count how many times you have counted 12:
text

1 finger  = 12
2 fingers = 24
3 fingers = 36
4 fingers = 48
5 fingers = 60

And 60 is the macro. No zero. No fractions. No decimals.
The Carry

The carry rolls until stable:
c

while (knuckles >= 12) { knuckles -= 12; fingers += 1; }
while (fingers >= 5)   { fingers -= 5;  macros  += 1; }

This is the Sumerian shift. It is applied after every operation.

The coordinate is the number of steps per scale. The carry is the shift between scales. The operations compute; the carry stores.
Files


Dedication

Terrence Andrew Davis (1969–2018) built his own temple from the bedrock up.
He defended architectural minimalism. He defended the integrity of native
binary execution. He never stopped talking to the silicon.

His core conviction — that compute stacks should remain mathematically
pristine, unencumbered by corporate software bloat, and transparent down to
the raw silicon clock cycle — is implemented in this framework.

Without him, we would never have continued with the mathematics.
