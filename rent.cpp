#include "sportsRental.h"

// Parent: rent.cpp
// Function: Displays all available equipment records.
// How it works: Loads equipment into a linked list, prints each node, then deletes the list.
void viewEquipment() {
    EquipmentNode* equipments = loadEquipments();

    if (equipments == NULL) {
        showError("No equipment records found.");
        return;
    }

    cout << "===== AVAILABLE EQUIPMENT =====" << endl;
    cout << fixed << setprecision(2);

    EquipmentNode* current = equipments;
    int itemNumber = 1;

    while (current != NULL) {
        cout << "[" << itemNumber << "] "
             << current->data.name
             << " | Quantity: " << current->data.quantity
             << " | Rate per day: " << current->data.ratePerDay
             << endl;

        itemNumber++;
        current = current->next;
    }

    deleteEquipmentList(equipments);
}

// Parent: rent.cpp
// Function: Lets the current user rent one equipment item for one day.
// How it works: Finds the equipment, decreases quantity, saves equipment, and appends a rental.
void rentEquipment(string username) {
    EquipmentNode* equipments = loadEquipments();
    string equipmentName;

    if (equipments == NULL) {
        showError("No equipment available for rental.");
        return;
    }

    cout << "===== AVAILABLE EQUIPMENT =====" << endl;
    cout << fixed << setprecision(2);

    EquipmentNode* currentEquipment = equipments;
    int itemNumber = 1;

    while (currentEquipment != NULL) {
        cout << "[" << itemNumber << "] "
             << currentEquipment->data.name
             << " | Quantity: " << currentEquipment->data.quantity
             << " | Rate per day: " << currentEquipment->data.ratePerDay
             << endl;

        itemNumber++;
        currentEquipment = currentEquipment->next;
    }

    cout << "Enter equipment name: ";
    getline(cin, equipmentName);

    if (containsComma(equipmentName)) {
        deleteEquipmentList(equipments);
        showError("Equipment name cannot contain commas.");
        return;
    }

    EquipmentNode* equipmentNode = findEquipment(equipments, equipmentName);

    if (equipmentNode == NULL) {
        deleteEquipmentList(equipments);
        showError("Equipment not found.");
        return;
    }

    if (equipmentNode->data.quantity <= 0) {
        deleteEquipmentList(equipments);
        showError("Equipment is not available.");
        return;
    }

    Rental rental;
    rental.equipment = equipmentName;
    rental.totalCost = equipmentNode->data.ratePerDay;
    rental.returned = 0;

    ensureRentalFolderExists();
    ofstream outFile(getUserRentalFile(username), ios::app);

    if (!outFile.is_open()) {
        deleteEquipmentList(equipments);
        showError("Unable to open rentals file.");
        return;
    }

    equipmentNode->data.quantity--;

    if (!saveEquipments(equipments)) {
        deleteEquipmentList(equipments);
        showError("Unable to save equipment file.");
        return;
    }

    outFile << rental.equipment << ","
            << rental.totalCost << ","
            << rental.returned << endl;

    cout << fixed << setprecision(2);
    cout << "Rental successful. Total cost: " << rental.totalCost << endl;
    deleteEquipmentList(equipments);
    pauseScreen();
}
