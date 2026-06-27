#include "sportsRental.h"

int main(){
    int loginStatus;
    int choice;
    string user;

    loginStatus = getUser(user);
    
    while (true) {
        if (!loginStatus) {
            displayAuth();
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                    cout << "Invalid Input. Please try again." << endl;
                    break;
            }
        } else {
            displayMenu(user);
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(choice) {
                case 1:
                    cout << "Rent Equipment feature is not available yet." << endl;
                    break;
                case 2:
                    cout << "Return Equipment feature is not available yet." << endl;
                    break;
                case 3:
                    cout << "Rental History feature is not available yet." << endl;
                    break;
                case 4:
                    logOut();
                    user = "";
                    loginStatus = 0;
                    break;
                case 5:
                    return 0;
                default:
                    cout << "Invalid Input. Please try again." << endl;
                    break;
            }
            
        }
    }

    return 0;
}
