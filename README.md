ULDA Topological Decoder Engine

A base-60 register with one operation: the peel.

Integer-only. No floating-point. No division. No modulo. Only: subtract odd numbers, count steps, fill ranks.
What It Does

The engine is one operation: the peel.
c

peel(7) = [2, 1, 1, 1]

The peel subtracts odd numbers (1, 3, 5, ...), counts the steps, and fills the ranks. That is the coordinate of the number — not the notation, but the structure.

The peel is division-free. The applications built on it are not: div(a, b) computes a / b and then peels the result. The peel is the storage; the application is the computation.

And everything is peel:
c

add(a, b) = peel(a + b)
sub(a, b) = peel(a - b)
mul(a, b) = peel(a * b)
div(a, b) = peel(a / b)
mod(a, b) = peel(a % b)
pow(a, n) = peel(a^n)
gcd(a, b) = peel(gcd(a, b))

One tool, many applications.
3 × (1/3) = 1

No float, no rounding, no remainder. The fraction closes.
c

peel(1) = [1]

The Five Functions and the Operator
text

1   = origin
2   = divider
3   = three axes
4   = four corners
5   = steps
6   = operator
60  = base
360 = wheel

And the wheel closes in two ways:
text

6 × 60 = 360 (steps, linear)
5 × 72 = 360 (rotation, cyclic)

Both are true. One is linear, the other is cyclic. Together they tell the story of the wheel. 
What the Engine Does Not Claim

The engine does not claim to compute without division. It claims to store without zeros.

The peel is the coordinate. The coordinate is the peel. The applications compute with division; the peel stores without it. That is the distinction.
Dedication

Terrence Andrew Davis (1969–2018) built his own temple from the bedrock up. He defended architectural minimalism. He defended the integrity of native binary execution. He never stopped talking to the silicon.

His core conviction — that compute stacks should remain mathematically pristine, unencumbered by corporate software bloat, and transparent down to the raw silicon clock cycle — is implemented in this framework.

Without him, we would never have continued with the mathematics.
License

AGPL-3.0. For commercial use that does not comply with AGPL-3.0, a commercial license is required. See LICENSE and COMMERCIAL_LICENSE.md.

Contact: jornepel@gmail.com

END README
