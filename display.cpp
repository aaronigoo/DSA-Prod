#include "sportsRental.h"

// ======================================================
// DISPLAY FUNCTIONS ONLY
// ======================================================

void displayAuth() {
    cout << "===== SPORTS RENTAL EQUIPMENT SYSTEM =====" << endl;
    cout << "Please Log in or Sign up to continue." << endl;
    cout << "==========================================" << endl;
    cout << "[1] - Sign Up" << endl;
    cout << "[2] - Log In" << endl;
    cout << "[3] - Forgot Password" << endl;
    cout << "[4] - Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Your Choice: ";
}

void displayMenu(string user) {
    cout << "===== SPORTS RENTAL EQUIPMENT SYSTEM =====" << endl;
    cout << "Welcome, " << user << "!" << endl;
    cout << "==========================================" << endl;
    cout << "[1] - Rent Equipment" << endl;
    cout << "[2] - Return Equipment" << endl;
    cout << "[3] - View Rental History" << endl;
    cout << "[4] - Log Out" << endl;
    cout << "[5] - Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Your Choice: ";

}