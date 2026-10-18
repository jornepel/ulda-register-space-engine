import sys

def ulda_register_converter(number):
    """Translates a standard integer into Base-60 [Geš, Units] coordinates."""
    if number < 0:
        return f"-[{abs(number) // 60}, {abs(number) % 60}]"
    return f"[{number // 60}, {number % 60}]"

def execute_socratic_root(target, precision_depth=2):
    """Peels the field using consecutive odd numbers across sexagesimal layers.
    
    Eliminates floating-point division noise by passing remainders down as 
    whole-unit scale inputs to sub-registers.
    """
    current_value = target
    results_layers = []
    
    for layer in range(precision_depth + 1):
        step = 1
        steps_taken = 0
        
        while current_value >= step:
            current_value -= step
            step += 2
            steps_taken += 1
            
        results_layers.append((steps_taken, current_value))
        # Shift execution vector down to the next smaller gear clock layer (60x multiplier)
        current_value *= 60
        
    return results_layers

def run_calculator():
    print("=" * 60)
    print("     UNIFIED LINEAGE DATA ARCHITECTURE (ULDA) CALCULATOR     ")
    print("      NATIVE SYSTEM OVERRIDE | BASE-60 CYCLIC MATRIX         ")
    print("=" * 60)
    print("Instructions: Enter any whole number to execute the matrix layout.")
    print("Type 'exit' to clear the field.\n")
    
    while True:
        user_input = input("Enter Target Number (Integer): ").strip()
        if user_input.lower() == 'exit':
            print("\nRegister cleared. Standing down.")
            sys.exit()
            
        try:
            target = int(user_input)
            if target < 1:
                print("Error: Input must be a positive, active non-zero value.\n")
                continue
        except ValueError:
            print("Error: Invalid entry. Please enter a valid structural integer.\n")
            continue
            
        # 1. Coordinate Translation
        coords = ulda_register_converter(target)
        
        # 2. Execute Radical Structural Search
        layers = execute_socratic_root(target, precision_depth=2)
        
        # 3. Print the Hard Hardware Blueprint
        print("\n" + "-" * 50)
        print(f"HARDWARE ANALYSIS RUN FOR TARGET: {target}")
        print("-" * 50)
        print(f"Base-60 Spatial Coordinate : {coords}")
        print(f"Macro-Scale Structure (60⁰): Zijde = {layers[0][0]}, Rest = {layers[0][1]}")
        
        if layers[0][1] > 0:
			print(f"Minutes-Layer Shift (60⁻¹): Sub-Zijde = {layers[1][0]}, Sub-Rest = {layers[1][1]}")
			print(f"Seconds-Layer Shift (60⁻²): Micro-Zijde = {layers[2][0]}, Final Remainder = {layers[2][1]}")
        else:
            print("Matrix Status             : Zero Margin Closure Achieved on the Macro Scale.")
        print("-" * 50 + "\n")

if __name__ == "__main__":
    run_calculator()
