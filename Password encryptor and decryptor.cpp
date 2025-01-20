#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

// Structure to store username-password pairs
struct User {
    string username;
    string encryptedPassword;
};

// Structure for storing date of birth
struct dob {
    int d, m, y;
} a;

string name, second_name, email;
int age;

// Password validation class
class Password {
private:
    string pass;

public:
    void input(const string &user_name, const string &user_second_name, const string &user_email, const int user_age) {
        while (true) {
            cout << "Enter the password: ";
            cin >> pass;

            // Check for password length (minimum length of 8)
            if (pass.length() < 8) {
                cout << "Password should be at least 8 characters long.\n";
                continue;
            }

            // Check for personal details in the password
            if (personalCheck(user_name, user_second_name, user_email, user_age)) {
                cout << "Password contains personal details, enter a new one.\n";
                continue;
            }

            // Check for at least one special character and one number
            bool containsSpecial = false;
            bool containsNumber = false;
            for (char ch : pass) {
                if (!isspace(ch) && ispunct(ch)) { // Check for special characters
                    containsSpecial = true;
                }
                if (isdigit(ch)) { // Check for numbers
                    containsNumber = true;
                }
            }

            if (!containsSpecial) {
                cout << "Password must contain at least one special character.\n";
                continue;
            }

            if (!containsNumber) {
                cout << "Password must contain at least one number.\n";
                continue;
            }

            // Check for password strength
            string strength = checkStrength();
            if (strength == "weak") {
                cout << "Password is too weak. Please try again.\n";
                continue;
            }

            break; // Exit the loop when password is valid
        }
    }

    string getPassword() {
        return pass;
    }

    // Convert string to lowercase
    string toLowercase(const string& str) {
        string lower_str = str;
        transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
        return lower_str;
    }

    // Check if password contains personal details (name, second name, email, age, date of birth)
    bool personalCheck(const string &user_name, const string &user_second_name, const string &user_email, const int user_age) {
        string lower_pass = toLowercase(pass);
        string lower_name = toLowercase(user_name);
        string lower_second_name = toLowercase(user_second_name);
        string lower_email = toLowercase(user_email);

        // Check if the date of birth matches in any reasonable format
        string dob_concatenated = to_string(a.d) + to_string(a.m) + to_string(a.y);
        string dob_dmy = to_string(a.d) + "/" + to_string(a.m) + "/" + to_string(a.y);
        string dob_mdy = to_string(a.m) + "/" + to_string(a.d) + "/" + to_string(a.y);
        string dob_ymd = to_string(a.y) + to_string(a.m) + to_string(a.d);

        if (lower_pass.find(lower_name) != string::npos ||
            lower_pass.find(lower_second_name) != string::npos ||
            lower_pass.find(lower_email) != string::npos ||
            lower_pass.find(to_string(user_age)) != string::npos ||
            lower_pass.find(dob_concatenated) != string::npos ||
            lower_pass.find(dob_dmy) != string::npos ||
            lower_pass.find(dob_mdy) != string::npos ||
            lower_pass.find(dob_ymd) != string::npos) {
            return true;
        }
        return false;
    }

    // Check password strength
    string checkStrength() {
        int l = 0, u = 0, d = 0, s = 0, c = 0;
        for (char ch : pass) {
            if (islower(ch)) l++;               // Check for lowercase
            else if (isupper(ch)) u++;          // Check for uppercase
            else if (isdigit(ch)) d++;          // Check for digits
            else if (!isspace(ch) && ispunct(ch)) c++;  // Check for special characters (punctuation)
            else if (isspace(ch)) s++;          // Count spaces (for weak password)
        }

        if (s > 0) return "weak";  // Password contains spaces, which is weak
        if (l > 0 && u > 0 && d > 0 && c > 0) return "strong";  // Strong if it contains lower, upper, digits, and special characters
        if ((l > 0 && u > 0) || (l > 0 && d > 0) || (u > 0 && d > 0)) return "moderate";  // Moderate if it contains at least two of the types
        return "weak";  // Return weak if it doesn't meet the criteria
    }
};

// Prepare input by ensuring even-length strings (keep all characters)
string prepareInput(string str) {
    if (str.length() % 2 != 0) {
        str += 'x'; // Padding for odd-length input
    }
    return str;
}

// Encryption function
string encryption(string &str, vector<vector<char>> &mat, map<char, pair<int, int>> &posn) {
    string encrypt = "";
    for (int i = 0; i < str.size(); i += 2) {
        char a = str[i], b = str[i + 1];
        auto posA = posn[a], posB = posn[b];
        if (posA.first == posB.first) { // Same row
            encrypt += mat[posA.first][(posA.second + 1) % mat[0].size()];
            encrypt += mat[posB.first][(posB.second + 1) % mat[0].size()];
        } else if (posA.second == posB.second) { // Same column
            encrypt += mat[(posA.first + 1) % mat.size()][posA.second];
            encrypt += mat[(posB.first + 1) % mat.size()][posB.second];
        } else { // Rectangle swap
            encrypt += mat[posA.first][posB.second];
            encrypt += mat[posB.first][posA.second];
        }
    }
    return encrypt;
}

// Decryption function
string decryption(string &str, vector<vector<char>> &mat, map<char, pair<int, int>> &posn) {
    string decrypt = "";
    for (int i = 0; i < str.size(); i += 2) {
        char a = str[i], b = str[i + 1];
        auto posA = posn[a], posB = posn[b];
        if (posA.first == posB.first) { // Same row
            decrypt += mat[posA.first][(posA.second + mat[0].size() - 1) % mat[0].size()];
            decrypt += mat[posB.first][(posB.second + mat[0].size() - 1) % mat[0].size()];
        } else if (posA.second == posB.second) { // Same column
            decrypt += mat[(posA.first + mat.size() - 1) % mat.size()][posA.second];
            decrypt += mat[(posB.first + mat.size() - 1) % mat.size()][posB.second];
        } else { // Rectangle swap
            decrypt += mat[posA.first][posB.second];
            decrypt += mat[posB.first][posA.second];
        }
    }

    // Remove padding 'x' if it exists at the end
    if (!decrypt.empty() && decrypt.back() == 'x') {
        decrypt.pop_back();
    }

    return decrypt;
}

// Generate key matrix to include alphanumeric and special characters
void generateKeyMatrix(string key, vector<vector<char>> &mat, map<char, pair<int, int>> &posn) {
    string processedKey = "";
    map<char, bool> used;

    // Process key (remove duplicates)
    for (char c : key) {
        if (!used[c]) {
            processedKey += c;
            used[c] = true;
        }
    }

    // Fill matrix with processed key and remaining characters
    int idx = 0;
    for (char c : processedKey) {
        mat[idx / 10][idx % 10] = c;
        posn[c] = {idx / 10, idx % 10};
        idx++;
    }

    // Include other characters (digits, symbols) from the ASCII table
    for (int i = 32; i < 127; i++) { // ASCII printable characters
        char c = (char)i;
        if (!used[c]) {
            mat[idx / 10][idx % 10] = c;
            posn[c] = {idx / 10, idx % 10};
            used[c] = true;
            idx++;
        }
    }
}

// Check if the encrypted password exists in the system for a given username
string getPasswordByUsername(const vector<User> &users, const string &username) {
    for (const auto &user : users) {
        if (user.username == username) {
            return user.encryptedPassword;
        }
    }
    return "";  // Return an empty string if username not found
}

int main() {
    srand(time(0));

    // Predetermined keys
    vector<string> keys = {"Samridhi", "Saksham", "Yashaswini"};

    // Randomly choose a key
    string selectedKey = keys[rand() % keys.size()];

    // Generate key matrix
    vector<vector<char>> mat(10, vector<char>(10)); // 10x10 matrix to fit 100 characters
    map<char, pair<int, int>> posn;
    generateKeyMatrix(selectedKey, mat, posn);

    // Vector to store users
    vector<User> users;

    while (true) {
        // Display menu
        int choice;
        cout << "\nChoose an option:\n1. Register user\n2. Decrypt password\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            // Input username
            string username;
            cout << "Enter username: ";
            cin >> username;

            // Input user details
            cout << "Enter the name: ";
            cin.ignore(); // To clear input buffer
            getline(cin, name);

            cout << "Enter the second name: ";
            getline(cin, second_name);

            cout << "Enter the email: ";
            getline(cin, email);

            cout << "Enter age: ";
            cin >> age;

            cout << "Enter date of birth (day month year): ";
            cin >> a.d >> a.m >> a.y;

            // Validate password
            Password passValidator;
            passValidator.input(name, second_name, email, age); // Pass second name for validation
            string password = passValidator.getPassword();

            // Prepare the password for encryption
            password = prepareInput(password);

            // Encrypt the password
            string encryptedPassword = encryption(password, mat, posn);

            // Store the username and encrypted password
            users.push_back({username, encryptedPassword});

            // Display success message and encrypted password
            cout << "\nUser \"" << username << "\" registered successfully!" << endl;
            cout << "Encrypted password for user \"" << username << "\": " << encryptedPassword << endl;
        } else if (choice == 2) {
            // Input username to decrypt the password
            string username;
            cout << "Enter the username to retrieve and decrypt the password: ";
            cin >> username;

            // Retrieve the encrypted password by username
            string encryptedText = getPasswordByUsername(users, username);

            if (!encryptedText.empty()) {
                // Decrypt the password
                string decryptedPassword = decryption(encryptedText, mat, posn);

                // Display the decrypted password
                cout << "\nDecrypted password for user \"" << username << "\": " << decryptedPassword << endl;
            } else {
                cout << "\nUsername not found in the system!" << endl;
            }
        } else if (choice == 3) {
            // Exit the program
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
