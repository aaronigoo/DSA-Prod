#include "sportsRental.h"

// Parent: return.cpp
// Function: Lets the current user return an active rental.
// How it works: Loads the user's rentals, marks the chosen active rental returned, and restores quantity.
void returnEquipment(string username) {
    RentalNode* rentals = loadRentals(username);
    RentalNode* selectedRental = NULL;
    int choice;
    int activeCount = 0;

    cout << "===== ACTIVE RENTALS =====" << endl;

    RentalNode* current = rentals;

    while (current != NULL) {
        if (current->data.returned == 0) {
            activeCount++;
            cout << "[" << activeCount << "]" << endl;
            displayRental(current->data);
            cout << "--------------------------" << endl;
        }

        current = current->next;
    }

    if (activeCount == 0) {
        deleteRentalList(rentals);
        showError("You have no active rentals to return.");
        return;
    }

    readInt("Choose rental to mark as returned: ", choice);

    if (choice < 1 || choice > activeCount) {
        deleteRentalList(rentals);
        showError("Invalid choice.");
        return;
    }

    current = rentals;
    activeCount = 0;

    while (current != NULL && selectedRental == NULL) {
        if (current->data.returned == 0) {
            activeCount++;

            if (activeCount == choice) {
                selectedRental = current;
            }
        }

        current = current->next;
    }

    EquipmentNode* equipments = loadEquipments();
    EquipmentNode* equipmentNode = findEquipment(equipments, selectedRental->data.equipment);

    if (equipmentNode == NULL) {
        deleteRentalList(rentals);
        deleteEquipmentList(equipments);
        showError("Unable to find equipment record.");
        return;
    }

    selectedRental->data.returned = 1;
    equipmentNode->data.quantity++;

    if (!saveEquipments(equipments) || !saveRentals(username, rentals)) {
        deleteRentalList(rentals);
        deleteEquipmentList(equipments);
        showError("Unable to save return.");
        return;
    }

    deleteRentalList(rentals);
    deleteEquipmentList(equipments);
    showMessage("Equipment marked as returned.");
}
