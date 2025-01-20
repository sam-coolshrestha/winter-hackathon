#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string name, email;
int age;

struct dob {
    int d, m, y;
} a;

class password {
private:
    int l = 0, u = 0, d = 0, s = 0, c = 0, score = 0;
    char ch;

public:
    string pass;

    void input() {
        while (true) {
            cout << "Enter the password: ";
            cin >> pass;
            if (pass.length() < 8) {
                cout << "Length of Password should be more than or equal to 8" << endl;
                continue;
            }
            if (PersonalCheck()) {
                cout << "Password contains personal details, Enter a new one" << endl;
                continue;
            }
            break; // Exit loop when password passes basic validation
        }
    }

    string to_lowercase(const string& str) {
        string lower_str = str;
        transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
        return lower_str;
    }

    bool PersonalCheck() {
        string lower_pass = to_lowercase(pass);
        string lower_name = to_lowercase(name);
        string lower_email = to_lowercase(email);

        // Check if the date of birth matches in any reasonable format
        string dob_concatenated = to_string(a.d) + to_string(a.m) + to_string(a.y);
        string dob_dmy = to_string(a.d) + "/" + to_string(a.m) + "/" + to_string(a.y);
        string dob_mdy = to_string(a.m) + "/" + to_string(a.d) + "/" + to_string(a.y);
        string dob_ymd = to_string(a.y) + to_string(a.m) + to_string(a.d);
        string date=to_string(a.y);
        string month=to_string(a.m);
        string year=to_string(a.y);

        // Check if password contains any personal detail
        if (lower_pass.find(lower_name) != string::npos ||
            lower_pass.find(lower_email) != string::npos ||
            lower_pass.find(to_string(age)) != string::npos ||
            lower_pass.find(dob_concatenated) != string::npos ||
            lower_pass.find(dob_dmy) != string::npos ||
            lower_pass.find(dob_mdy) != string::npos ||
            lower_pass.find(dob_ymd) != string::npos||
            lower_pass.find(date)!=string::npos ||
            lower_pass.find(month)!=string::npos ||
            lower_pass.find(year)!=string::npos)
            {return true;
        }
        return false;
    }

    string checkStrength() {
        l = u = d = s = c = score = 0;
        for (char ch : pass) {
            if (islower(ch)) l++;
            else if (isupper(ch)) u++;
            else if (isdigit(ch)) d++;
            else if (isspace(ch)) s++;
            else c++;
        }
        if (l != 0) score++;
        if (u != 0) score++;
        if (d != 0) score++;
        if (c != 0) score++;
        if (s != 0) score--; // Penalize spaces

        if (score == 4) return "strong";
        else if (score == 3) return "moderate";
        return "weak";
    }
};

string generate_pass() {
    cout << "Enter the name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);
    cout << "Enter the email id: ";
    cin >> email;
    cout << "Enter the age: ";
    cin >> age;
    cout << "Enter the date of birth in dd/mm/yyyy format:" << endl;
    cout << "Enter the date: ";
    cin >> a.d;
    cout << "Enter the month: ";
    cin >> a.m;
    cout << "Enter the year: ";
    cin >> a.y;

    password p;
    string strength;

    while (true) {
        p.input(); // Input the password
        strength = p.checkStrength();
        if (strength == "strong") {
            cout << "Congrats! Password created successfully" << endl;
            break; // Exit loop on strong password
        } else if (strength == "moderate") {
            cout << "Password is moderate. Consider adding more complexity." << endl;
        } else {
            cout << "Password is weak. Enter a stronger one." << endl;
        }
    }
    return p.pass;
}

int main() {
    vector<string> P;
    string passcode, choice;

    while (true) {
        cout << "*" << endl;
        passcode = generate_pass();
        P.push_back(passcode);

        cout << "Do you wish to enter more (Y or N): ";
        cin >> choice;

        if (choice == "N" || choice == "n") {
            break; // Exit the loop if the user chooses 'N'
        }
    }

    // Optionally display all generated passcodes
    cout << "\nGenerated Passcodes:" << endl;
    for (const string& pass : P) {
        cout << pass << endl;
    }

    return 0;
}
