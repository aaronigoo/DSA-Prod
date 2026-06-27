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

    readText("Enter username: ", username);
    readText("Enter password: ", password);

    if (hasComma(username) || hasComma(password)) {
        showError("Username and password cannot contain commas.");
        return;
    }

    if (findUser(username, existingPassword)) {
        showError("Username already exists. Please choose another name or log in instead.");
        return;
    }

    ofstream outFile("files/users", ios::app);

    if (!outFile.is_open()) {
        showError("Unable to open users file.");
        return;
    }

    outFile << username << "," << password << endl;
    showMessage("Sign up successful. You may now log in.");
}

int logIn(string &user) {
    string username;
    string password;
    string savedPassword;

    readText("Enter username: ", username);
    readText("Enter password: ", password);

    if (!findUser(username, savedPassword) || savedPassword != password) {
        showError("Invalid username or password.");
        return 0;
    }

    ofstream outFile("files/userdata");

    if (!outFile.is_open()) {
        showError("Unable to save logged in user.");
        return 0;
    }

    outFile << username << endl;
    user = username;
    showMessage("Login successful.");
    return 1;
}

void forgotPassword() {
    string username;
    string password;

    readText("Enter username: ", username);

    if (findUser(username, password)) {
        cout << "Your password is: " << password << endl;
        pauseScreen();
    } else {
        showError("Username not found.");
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
    showMessage("Logged out successfully.");
}
