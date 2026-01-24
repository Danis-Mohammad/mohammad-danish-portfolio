def calculate_bmi():
    print("--- BMI Calculator ---")
    
    try:
        # 1. Get user input
        weight = float(input("Enter your weight in kilograms (kg): "))
        height = float(input("Enter your height in meters (m): "))

        # Check for realistic positive numbers
        if weight <= 0 or height <= 0:
            print("Error: Weight and height must be positive numbers.")
            return

        # 2. Calculate BMI
        # Formula: weight (kg) / [height (m)]^2
        bmi = weight / (height ** 2)

        # 3. Determine Category
        if bmi < 18.5:
            category = "Underweight"
        elif 18.5 <= bmi < 25:
            category = "Normal weight"
        elif 25 <= bmi < 30:
            category = "Overweight"
        else:
            category = "Obesity"

        # 4. Display Result
        print("-" * 25)
        print(f"Your BMI is: {bmi:.2f}")
        print(f"Category: {category}")
        print("-" * 25)

    except ValueError:
        print("\nInvalid input. Please enter numeric values only (e.g., 70.5 or 1.75).")
    except Exception as e:
        print(f"\nAn unexpected error occurred: {e}")

if __name__ == "__main__":
    calculate_bmi()