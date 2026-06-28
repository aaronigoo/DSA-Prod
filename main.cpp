#include "sportsRental.h"

int main(){
    int loginStatus;
    int choice;
    string user;

    loginStatus = getUser(user);
    
    while (true) {
        if (!loginStatus) {
            clearScreen();
            displayAuth();
            if (!readIntOnce("", choice)) {
                continue;
            }
            clearScreen();

            switch(choice) {
                case 1:
                    signUp();
                    break;
                case 2:
                    loginStatus = logIn(user);
                    break;
                case 3:
                    forgotPassword();
                    break;
                case 4:
                    return 0;
                default:
                    showError("Invalid Input. Please try again.");
                    break;
            }
        } else {
            clearScreen();
            displayMenu(user);
            if (!readIntOnce("", choice)) {
                continue;
            }
            clearScreen();

            switch(choice) {
                case 1:
                    //rentEquipment(user); //remove comment for your own function.
                    break;
                case 2:
                    //returnEquipment(user); //remove comment for your own function.
                    break;
                case 3:
                    //viewRentalHistory(user); //remove comment for your own function.
                    break;
                case 4:
                    logOut();
                    user = "";
                    loginStatus = 0;
                    break;
                case 5:
                    return 0;
                default:
                    showError("Invalid Input. Please try again.");
                    break;
            }
            
        }
    }

    return 0;
}
