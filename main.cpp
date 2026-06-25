#include "sportsRental.h"

int main(){
    int loginStatus = 0;
    string user;
    
    while (loginStatus) {
        choice = "0";
        displayAuth();
        cin >> choice;
        cin.ignore;
        switch(choice) {
            case 1:
                signUp();
                break;
            case 2:
                loginStatus = logIn(&user);
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                return;
            default:
                cout << "Invalid Input. Please try again." << endl;
                break;
        }
}