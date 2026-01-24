import string
import secrets

def generate_password():
    print("--- Secure Password Generator ---")

    # 1. Get Password Length with Validation
    while True:
        try:
            length_input = input("Enter password length (minimum 4): ")
            length = int(length_input)
            
            if length < 4:
                print("Error: Password must be at least 4 characters long to be secure.")
                continue
            break
        except ValueError:
            print("Invalid input. Please enter a whole number.")

    # 2. Get Character Preferences
    print("\nSelect character types to include:")
    use_letters = input("Include letters (a-z, A-Z) [y/n]: ").strip().lower().startswith('y')
    use_digits  = input("Include numbers (0-9)      [y/n]: ").strip().lower().startswith('y')
    use_symbols = input("Include symbols (!@#$%)    [y/n]: ").strip().lower().startswith('y')

    # 3. Build the Character Pool
    char_pool = ""
    if use_letters:
        char_pool += string.ascii_letters
    if use_digits:
        char_pool += string.digits
    if use_symbols:
        char_pool += string.punctuation

    # 4. Generate and Display Password
    if not char_pool:
        print("\nError: You must select at least one character type.")
        return

    # Create the password using secrets.choice for cryptographic security
    password = ''.join(secrets.choice(char_pool) for _ in range(length))

    print("-" * 30)
    print(f"Generated Password: {password}")
    print("-" * 30)

if __name__ == "__main__":
    generate_password()