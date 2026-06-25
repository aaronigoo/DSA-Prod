#include "sportsRental.h"

// ======================================================
// AUTHENTICATION FUNCTIONS ONLY
// ======================================================

void getUser(string &user) {
    ifstream inFile("files/userdata");
    if (inFile.is.open()) {
        user = inFile.getline();
        return 1;
    } else {
        return 0;
    }
}

string currentUser() {

}