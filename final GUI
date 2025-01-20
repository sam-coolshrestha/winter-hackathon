#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

// Structure to store username-password pairs
struct User {
    string username;
    string encryptedPassword;
};

// Prepare input by ensuring even-length strings (keep all characters)
string prepareInput(string str) {
    if (str.length() % 2 != 0) {
        str += 'x'; // Padding for odd-length input
    }
    return str;
}

// Helper function to convert string to lowercase
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
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

// Generate key matrix to include alphanumeric and special characters but exclude " ; ' ."
void generateKeyMatrix(string key, vector<vector<char>> &mat, map<char, pair<int, int>> &posn) {
    string processedKey = "";
    map<char, bool> used;

    // Process key (remove duplicates)
    for (char c : key) {
        if (!used[c] && c != ' ' && c != ';' && c != '.') { // Exclude blank space, semicolon, and dot
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

    // Include other characters (digits, symbols) from the ASCII table but exclude the unwanted ones
    for (int i = 32; i < 127; i++) { // ASCII printable characters
        char c = (char)i;
        if (!used[c] && c != ' ' && c != ';' && c != '.') { // Exclude blank space, semicolon, and dot
            mat[idx / 10][idx % 10] = c;
            posn[c] = {idx / 10, idx % 10};
            used[c] = true;
            idx++;
        }
    }
}

// Check if the encrypted password exists in the system
bool isPasswordStored(const vector<User> &users, const string &username, string &decryptedPassword) {
    for (const auto &user : users) {
        if (user.username == username) {
            decryptedPassword = user.encryptedPassword;
            return true;
        }
    }
    return false;
}

// Check if password contains personal details (case-insensitive)
bool containsPersonalDetails(const string &password, const string &name, const string &dob) {
    string lowerPassword = toLowerCase(password);
    string lowerName = toLowerCase(name);
    string lowerDob = toLowerCase(dob);

    if (lowerPassword.find(lowerName) != string::npos || lowerPassword.find(lowerDob) != string::npos) {
        return true;
    }
    return false;
}

HINSTANCE g_hInst;
HWND hFirstWindow, hSecondWindow, hRetrieveWindow;
HWND hUsernameEdit, hPasswordEdit, hStoreButton, hRetrieveButton, hQuitButton, hRetrieveUsernameEdit, hNameEdit, hDobEdit;  // Buttons and edit controls
vector<User> users;  // Vector to store users

// Window procedure declarations
LRESULT CALLBACK FirstWindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SecondWindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RetrieveWindowProc(HWND, UINT, WPARAM, LPARAM);

// Simplified Password Check Function
bool IsPasswordValid(const string &password) {
    if (password.length() < 8) return false; // Length check
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
        if (!isalnum(ch)) hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    g_hInst = hInst;

    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;

    wc.lpszClassName = L"FirstWindowClass";
    wc.lpfnWndProc = FirstWindowProc;
    if (!RegisterClassW(&wc)) return -1;

    wc.lpszClassName = L"SecondWindowClass";
    wc.lpfnWndProc = SecondWindowProc;
    if (!RegisterClassW(&wc)) return -1;

    wc.lpszClassName = L"RetrieveWindowClass";
    wc.lpfnWndProc = RetrieveWindowProc;
    if (!RegisterClassW(&wc)) return -1;

    hFirstWindow = CreateWindowW(L"FirstWindowClass", L"Password Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 300, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK FirstWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            // Create buttons for the menu options
            hStoreButton = CreateWindowW(L"button", L"Store Password", WS_VISIBLE | WS_CHILD, 50, 50, 150, 30, hWnd, (HMENU)1, g_hInst, NULL);
            hRetrieveButton = CreateWindowW(L"button", L"Retrieve Password", WS_VISIBLE | WS_CHILD, 50, 100, 150, 30, hWnd, (HMENU)2, g_hInst, NULL);
            hQuitButton = CreateWindowW(L"button", L"Quit", WS_VISIBLE | WS_CHILD, 50, 150, 150, 30, hWnd, (HMENU)3, g_hInst, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == 1) {  // Store Password button clicked
                ShowWindow(hWnd, SW_HIDE);
                hSecondWindow = CreateWindowW(L"SecondWindowClass", L"Enter Username, Name, DOB and Password", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 300, NULL, NULL, g_hInst, NULL);
            }
            else if (LOWORD(wp) == 2) {  // Retrieve Password button clicked
                ShowWindow(hWnd, SW_HIDE);
                hRetrieveWindow = CreateWindowW(L"RetrieveWindowClass", L"Retrieve Password", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 200, NULL, NULL, g_hInst, NULL);
            }
            else if (LOWORD(wp) == 3) {  // Quit button clicked
                PostQuitMessage(0);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK SecondWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            // Create input fields for Name, Date of Birth, and Username
            CreateWindowW(L"static", L"Name:", WS_VISIBLE | WS_CHILD, 50, 50, 80, 25, hWnd, NULL, g_hInst, NULL);
            hNameEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 180, 25, hWnd, NULL, g_hInst, NULL);

            CreateWindowW(L"static", L"DOB (DD/MM/YY):", WS_VISIBLE | WS_CHILD, 50, 100, 120, 25, hWnd, NULL, g_hInst, NULL);
            hDobEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 180, 25, hWnd, NULL, g_hInst, NULL);

            CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILD, 50, 150, 80, 25, hWnd, NULL, g_hInst, NULL);
            hUsernameEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 150, 180, 25, hWnd, NULL, g_hInst, NULL);

            CreateWindowW(L"static", L"Password:", WS_VISIBLE | WS_CHILD, 50, 200, 80, 25, hWnd, NULL, g_hInst, NULL);
            hPasswordEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 200, 180, 25, hWnd, NULL, g_hInst, NULL);

            CreateWindowW(L"button", L"Submit", WS_VISIBLE | WS_CHILD, 150, 250, 80, 30, hWnd, (HMENU)1, g_hInst, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == 1) {
                wchar_t buffer[100];

                GetWindowTextW(hNameEdit, buffer, 100);
                string name = string(buffer, buffer + wcslen(buffer));

                GetWindowTextW(hDobEdit, buffer, 100);
                string dob = string(buffer, buffer + wcslen(buffer));

                GetWindowTextW(hUsernameEdit, buffer, 100);
                string username = string(buffer, buffer + wcslen(buffer));

                GetWindowTextW(hPasswordEdit, buffer, 100);
                string password = string(buffer, buffer + wcslen(buffer));

                if (!IsPasswordValid(password)) {
                    MessageBoxW(hWnd, L"Password must be at least 8 characters long and include upper, lower, digit, and special character.", L"Error", MB_OK);
                }
                else if (containsPersonalDetails(password, name, dob)) {
                    MessageBoxW(hWnd, L"Password should not contain personal details like name or date of birth. Please choose a stronger password.", L"Error", MB_OK);
                }
                else {
                    password = prepareInput(password);
                    vector<vector<char>> mat(10, vector<char>(10)); // 10x10 matrix
                    map<char, pair<int, int>> posn;
                    generateKeyMatrix("Samridhi", mat, posn);
                    string encryptedPassword = encryption(password, mat, posn);

                    // Store the encrypted password
                    users.push_back({username, encryptedPassword});

                    MessageBoxW(hWnd, L"Password stored successfully.", L"Success", MB_OK);

                    // Go back to the first window to allow further actions
                    ShowWindow(hWnd, SW_HIDE);
                    hFirstWindow = CreateWindowW(L"FirstWindowClass", L"Password Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 300, NULL, NULL, g_hInst, NULL);
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK RetrieveWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILD, 50, 50, 80, 25, hWnd, NULL, g_hInst, NULL);
            hRetrieveUsernameEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 180, 25, hWnd, NULL, g_hInst, NULL);

            CreateWindowW(L"button", L"Retrieve", WS_VISIBLE | WS_CHILD, 150, 100, 80, 30, hWnd, (HMENU)1, g_hInst, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == 1) {
                wchar_t buffer[100];
                GetWindowTextW(hRetrieveUsernameEdit, buffer, 100);
                string username = string(buffer, buffer + wcslen(buffer));
                string encryptedPassword;

                if (isPasswordStored(users, username, encryptedPassword)) {
                    vector<vector<char>> mat(10, vector<char>(10)); // 10x10 matrix
                    map<char, pair<int, int>> posn;
                    generateKeyMatrix("Samridhi", mat, posn);
                    string decryptedPassword = decryption(encryptedPassword, mat, posn);
                    MessageBoxW(hWnd, (L"Decrypted Password: " + std::wstring(decryptedPassword.begin(), decryptedPassword.end())).c_str(), L"Password Retrieved", MB_OK);
                } else {
                    MessageBoxW(hWnd, L"Username not found.", L"Error", MB_OK);
                }

                // Go back to the first window to allow further actions
                ShowWindow(hWnd, SW_HIDE);
                hFirstWindow = CreateWindowW(L"FirstWindowClass", L"Password Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 300, NULL, NULL, g_hInst, NULL);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}
