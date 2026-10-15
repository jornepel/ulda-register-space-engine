def socratic_root_check(target):
    step = 1
    current = target
    steps_taken = 0
    while current >= step:
        current -= step
        step += 2
        steps_taken += 1
    return steps_taken, current

# Testcase 50 (√50 -> Zijde 7, Rest 1)
zijde, rest = socratic_root_check(50)
print(f"ULDA Root 50: Zijde = {zijde}, Rest = {rest} (Informatie voor de 60⁻¹ laag)")
