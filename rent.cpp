#include "sportsRental.h"

void viewEquipment() {
    EquipmentNode* equipments = loadEquipments();

    if (equipments == NULL) {
        showError("No equipment records found.");
        deleteEquipmentList(equipments);
        return;
    }

    cout << "===== AVAILABLE EQUIPMENT =====" << endl;

    EquipmentNode* current = equipments;
    int number = 1;

    while (current != NULL) {
        cout << "[" << number << "] " << current->data.name << endl;
        cout << "    Quantity: " << current->data.quantity << endl;
        cout << fixed << setprecision(2);
        cout << "    Rate Per Day: " << current->data.ratePerDay << endl;

        current = current->next;
        number++;
    }

    deleteEquipmentList(equipments);
}

void rentEquipment(string username) {
    EquipmentNode* equipments = loadEquipments();

    if (equipments == NULL) {
        showError("No equipment available for rental.");
        deleteEquipmentList(equipments);
        return;
    }

    cout << "===== AVAILABLE EQUIPMENT =====" << endl;

    EquipmentNode* current = equipments;
    int number = 1;

    while (current != NULL) {
        cout << "[" << number << "] " << current->data.name << endl;
        cout << "    Quantity: " << current->data.quantity << endl;
        cout << fixed << setprecision(2);
        cout << "    Rate Per Day: " << current->data.ratePerDay << endl;

        current = current->next;
        number++;
    }

    string equipmentName;
    cout << "Enter equipment name: ";
    getline(cin >> ws, equipmentName);

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
