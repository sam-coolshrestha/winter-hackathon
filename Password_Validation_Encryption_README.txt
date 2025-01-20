
# Password Validation and Encryption System

This program is a password validation and encryption system that ensures strong password security while allowing user registration and password retrieval.

---

## Features:
1. **Password Validation**:  
   - Ensures passwords are at least 8 characters long.  
   - Prohibits passwords containing personal details (e.g., name, email, date of birth).  
   - Requires at least one special character and one numeric digit.  
   - Evaluates password strength (weak, moderate, strong).  

2. **Password Encryption and Decryption**:  
   - Encrypts passwords using a custom matrix-based algorithm.  
   - Allows decryption of stored passwords for authenticated users.  

3. **User Registration**:  
   - Accepts username, name, email, age, and date of birth during registration.  
   - Encrypts the password for secure storage.  

4. **Password Retrieval**:  
   - Decrypts and retrieves stored passwords based on the username.  

---

## How It Works:

### 1. Register a User
- Enter a username.  
- Provide personal details (name, second name, email, age, date of birth).  
- Create a password that passes all validation checks.  
- The password is encrypted and stored alongside the username.

### 2. Decrypt a Password
- Input a username to retrieve the corresponding encrypted password.  
- The encrypted password is decrypted and displayed.  

---

## Key Technical Details:
1. **Password Validation**:  
   - The password is checked for personal details, such as the user's name, email, age, and date of birth in multiple formats.
   - Ensures a mix of uppercase, lowercase, digits, and special characters for strong passwords.  

2. **Key Matrix for Encryption**:  
   - A 10x10 matrix is generated using a random key from a predefined list.  
   - Matrix supports encryption and decryption of alphanumeric and special characters.  

3. **Encryption and Decryption**:  
   - Passwords are encrypted using the key matrix with a custom algorithm.  
   - Decryption reverses the process to recover the original password.  

---

## Code Instructions:
1. Compile the code using a C++ compiler:
   ```
   g++ -o PasswordSystem PasswordSystem.cpp
   ```
2. Run the program:
   ```
   ./PasswordSystem
   ```
3. Follow the menu options:
   - **Option 1**: Register a new user.  
   - **Option 2**: Decrypt and retrieve a password by username.  
   - **Option 3**: Exit the program.  

---

## Example:
**Register User**:  
- Input: `Username: john_doe`, `Password: @Secure123`.  
- Output: `Encrypted password: <encrypted_text>`.  

**Decrypt Password**:  
- Input: `Username: john_doe`.  
- Output: `Decrypted password: @Secure123`.  

---

## Security:
- Passwords are securely encrypted before storage.  
- The system ensures no sensitive information is leaked through weak passwords.  
