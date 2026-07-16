#include "sportsRental.h"
#include <queue>
#include <stack>
using namespace std;

void viewRentalHistory(string username) {
        RentalNode* rentalList = loadRentals(username);
    
    
    queue<Rental> oldestToNewest;
    stack<Rental> newestToOldest;
    int choice;
    
    
    RentalNode* current = rentalList;
    while (current != nullptr) {
        oldestToNewest.push(current->data);
        newestToOldest.push(current->data);
        current = current->next;
    }
    
    
    deleteRentalList(rentalList);
    
    
    if (oldestToNewest.empty()) {
        showError("No rental history found.");
        return;
    }
    
   
    cout << "\nRental History\n";
    cout << "1. Oldest to Newest\n";
    cout << "2. Newest to Oldest\n";
    cout << "Enter choice: ";
    readInt("", choice);
    
    
    switch(choice) {
        case 1:
            cout << "\nOldest to Newest:\n";
            while (!oldestToNewest.empty()) {
                displayRental(oldestToNewest.front());
                oldestToNewest.pop();
                if (!oldestToNewest.empty()) {
                    cout << "-------------------\n";
                }
            }
            break;
        case 2:
            cout << "\nNewest to Oldest:\n";
            while (!newestToOldest.empty()) {
                displayRental(newestToOldest.top());
                newestToOldest.pop();
                if (!newestToOldest.empty()) {
                    cout << "-------------------\n";
                }
            }
            break;
        default:
            showError("Invalid choice.");
    }
    
    
    pauseScreen();
}