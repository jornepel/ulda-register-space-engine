# ULDA Integer Purge Patch

**Doel:** floating-point en niet-integere resten uit een bestaande compute-stack verwijderen.

**Methode:** alle coördinaten, tijdstappen en carry-regels door de Look-Up Logic Matrix (LUM) halen.

**Effect:** radix-drift verdwijnt, de registers blijven schoon, de 504-grens blijft intact.

---

## Wat het doet

- **Geen floating-point.**
- **Geen `//` of `%`.**
- **Pure subtractie-carries.**
- **18-bit bit-slices.**
- **504 hardwired boundary.**
- **216 macro-envelope.**
- **De 6-Cipher blijft intact.**
- **En het register blijft schoon.**

---

## Installatie

```bash
git clone https://github.com/[jouw-gebruikersnaam]/ulda-integer-purge.git
cd ulda-integer-purge
python integer_purge.py
