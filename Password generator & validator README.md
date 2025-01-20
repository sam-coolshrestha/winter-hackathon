
# Password Strength Checker and Generator

This C++ program allows users to create secure passwords by checking their strength and ensuring that the passwords do not contain personal details like name, email, age, or date of birth.

## Features

- **Personal Detail Check**: Ensures that the password does not include sensitive personal details such as name, email, age, or date of birth in various formats.
- **Strength Validation**: Evaluates the password strength as 'weak', 'moderate', or 'strong' based on the inclusion of lowercase letters, uppercase letters, digits, special characters, and spaces.
- **Password Generation**: Prompts users to create a password until a 'strong' password is generated.
- **Storage of Passwords**: Stores all generated passwords in a vector and displays them at the end.

## How to Use

1. Compile the program using a C++ compiler (e.g., g++).
2. Run the executable file.
3. Enter personal details when prompted, including name, email, age, and date of birth.
4. Input passwords until a 'strong' password is created.
5. View all generated passwords at the end of the program.

## Code Flow

1. The user enters personal information.
2. The program prompts the user to create a password.
3. Each password is checked for:
   - Length (minimum of 8 characters)
   - Inclusion of personal details
   - Strength (based on character variety)
4. The user is guided to create a 'strong' password if the entered password is not strong enough.
5. All generated passwords are displayed at the end.

## Example Input/Output

### Input:
```
Enter the name: John Doe
Enter the email id: john.doe@example.com
Enter the age: 30
Enter the date of birth in dd/mm/yyyy format:
Enter the date: 15
Enter the month: 8
Enter the year: 1992
Enter the password: John1992!
Password contains personal details, Enter a new one
Enter the password: StrongPass@123
Congrats! Password created successfully
Do you wish to enter more (Y or N): N
```

### Output:
```
Generated Passcodes:
StrongPass@123
```

## Requirements

- A C++ compiler supporting C++11 or later.
- Basic understanding of C++ to modify or extend the functionality.

---

**Note**: Ensure that the program is used responsibly, as it handles sensitive personal details.
