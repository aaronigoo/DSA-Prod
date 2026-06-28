#include "sportsRental.h"

// Parent: history.cpp
// Function: Shows the current user's rental history.
// How it works: Loads rentals into a queue and stack so the user can choose display order.
void viewRentalHistory(string username) {
    RentalNode* rentals = loadRentals(username);
    queue<Rental> rentalQueue;
    stack<Rental> rentalStack;
    int choice;
    RentalNode* current = rentals;

    while (current != NULL) {
        rentalQueue.push(current->data);
        rentalStack.push(current->data);

        current = current->next;
    }

    deleteRentalList(rentals);

    if (rentalQueue.empty()) {
        showError("No rental history found.");
        return;
    }

    cout << "===== RENTAL HISTORY =====" << endl;
    cout << "[1] Oldest to Newest" << endl;
    cout << "[2] Newest to Oldest" << endl;
    readInt("Your Choice: ", choice);

    if (choice == 1) {
        while (!rentalQueue.empty()) {
            displayRental(rentalQueue.front());
            rentalQueue.pop();
            cout << "--------------------------" << endl;
        }
    } else if (choice == 2) {
        while (!rentalStack.empty()) {
            displayRental(rentalStack.top());
            rentalStack.pop();
            cout << "--------------------------" << endl;
        }
    } else {
        showError("Invalid choice.");
    }

    if (choice == 1 || choice == 2) {
        pauseScreen();
    }
}
