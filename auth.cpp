#include "sportsRental.h"

// ======================================================
// AUTHENTICATION FUNCTIONS ONLY
// ======================================================

bool hasComma(string text) {
    return text.find(',') != string::npos;
}

bool findUser(string username, string &password) {
    ifstream inFile("files/users");
    string line;

    while (getline(inFile, line)) {
        size_t commaPosition = line.find(',');

        if (commaPosition == string::npos) {
            continue;
        }

        string savedUsername = line.substr(0, commaPosition);
        string savedPassword = line.substr(commaPosition + 1);

        if (savedUsername == username) {
            password = savedPassword;
            return true;
        }
    }

    return false;
}

void signUp() {
    string username;
    string password;
    string existingPassword;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (hasComma(username) || hasComma(password)) {
        cout << "Username and password cannot contain commas." << endl;
        return;
    }

    if (findUser(username, existingPassword)) {
        cout << "Username already exists. Please choose\nanother name or log in instead." << endl;
        return;
    }

    ofstream outFile("files/users", ios::app);

    if (!outFile.is_open()) {
        cout << "Unable to open users file." << endl;
        return;
    }

    outFile << username << "," << password << endl;
    cout << "Sign up successful. You may now log in." << endl;
}

int logIn(string &user) {
    string username;
    string password;
    string savedPassword;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (!findUser(username, savedPassword) || savedPassword != password) {
        cout << "Invalid username or password." << endl;
        return 0;
    }

    ofstream outFile("files/userdata");

    if (!outFile.is_open()) {
        cout << "Unable to save logged in user." << endl;
        return 0;
    }

    outFile << username << endl;
    user = username;
    cout << "Login successful." << endl;
    return 1;
}

void forgotPassword() {
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    if (findUser(username, password)) {
        cout << "Your password is: " << password << endl;
    } else {
        cout << "Username not found." << endl;
    }
}

int getUser(string &user) {
    ifstream inFile("files/userdata");

    if (inFile.is_open() && getline(inFile, user) && !user.empty()) {
        return 1;
    }

    return 0;
}

void logOut() {
    remove("files/userdata");
    cout << "Logged out successfully." << endl;
}
