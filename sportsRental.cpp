#include "sportsRental.h"
#include <direct.h>

// ======================================================
// RENTAL FUNCTIONS ONLY
// ======================================================

const string EQUIPMENT_FILE = "files/equipments";
const string RENTAL_FOLDER = "files/rentals";

bool toInt(string text, int &value) {
    stringstream stream(text);
    stream >> value;
    return !stream.fail() && stream.eof();
}

bool toDouble(string text, double &value) {
    stringstream stream(text);
    stream >> value;
    return !stream.fail() && stream.eof();
}

bool containsComma(string text) {
    return text.find(',') != string::npos;
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    string line;

    cout << endl << "Press Enter to continue...";
    getline(cin, line);
}

void showMessage(string message) {
    cout << message << endl;
    pauseScreen();
}

void showError(string message) {
    cout << message << endl;
    pauseScreen();
}

bool readIntOnce(string prompt, int &value) {
    string line;

    if (!prompt.empty()) {
        cout << prompt;
    }

    getline(cin >> ws, line);
    stringstream stream(line);
    int parsedValue;
    char extraCharacter;

    if (stream >> parsedValue && !(stream >> extraCharacter)) {
        value = parsedValue;
        return true;
    }

    showError("Invalid input. Please enter a whole number.");
    return false;
}

void readInt(string prompt, int &value) {
    while (true) {
        if (readIntOnce(prompt, value)) {
            return;
        }
    }
}

void readText(string prompt, string &value) {
    cout << prompt;
    getline(cin >> ws, value);
}

void addEquipmentNode(EquipmentNode* &head, EquipmentNode* &tail, Equipment equipment) {
    EquipmentNode* newNode = new EquipmentNode;
    newNode->data = equipment;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void addRentalNode(RentalNode* &head, RentalNode* &tail, Rental rental) {
    RentalNode* newNode = new RentalNode;
    newNode->data = rental;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void deleteEquipmentList(EquipmentNode* head) {
    while (head != NULL) {
        EquipmentNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}

void deleteRentalList(RentalNode* head) {
    while (head != NULL) {
        RentalNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}

EquipmentNode* loadEquipments() {
    EquipmentNode* head = NULL;
    EquipmentNode* tail = NULL;
    ifstream inFile(EQUIPMENT_FILE);
    string line;

    while (getline(inFile, line)) {
        string quantityText;
        string rateText;
        string extraText;
        stringstream stream(line);
        Equipment equipment;

        if (!getline(stream, equipment.name, ',') ||
            !getline(stream, quantityText, ',') ||
            !getline(stream, rateText, ',') ||
            getline(stream, extraText, ',')) {
            continue;
        }

        if (!toInt(quantityText, equipment.quantity) || !toDouble(rateText, equipment.ratePerDay)) {
            continue;
        }

        if (!equipment.name.empty() && equipment.quantity >= 0 && equipment.ratePerDay >= 0) {
            addEquipmentNode(head, tail, equipment);
        }
    }

    return head;
}

bool saveEquipments(EquipmentNode* equipments) {
    ofstream outFile(EQUIPMENT_FILE);

    if (!outFile.is_open()) {
        return false;
    }

    EquipmentNode* current = equipments;

    while (current != NULL) {
        outFile << current->data.name << ","
                << current->data.quantity << ","
                << current->data.ratePerDay << endl;

        current = current->next;
    }

    return true;
}

void ensureRentalFolderExists() {
    _mkdir(RENTAL_FOLDER.c_str());
}

string getUserRentalFile(string username) {
    return RENTAL_FOLDER + "/" + username;
}

RentalNode* loadRentals(string username) {
    RentalNode* head = NULL;
    RentalNode* tail = NULL;
    ifstream inFile(getUserRentalFile(username));
    string line;

    while (getline(inFile, line)) {
        string totalCostText;
        string returnedText;
        string extraText;
        stringstream stream(line);
        Rental rental;

        if (!getline(stream, rental.equipment, ',') ||
            !getline(stream, totalCostText, ',') ||
            !getline(stream, returnedText, ',') ||
            getline(stream, extraText, ',')) {
            continue;
        }

        if (!toDouble(totalCostText, rental.totalCost) ||
            !toInt(returnedText, rental.returned)) {
            continue;
        }

        if (!rental.equipment.empty()) {
            addRentalNode(head, tail, rental);
        }
    }

    return head;
}

bool saveRentals(string username, RentalNode* rentals) {
    ensureRentalFolderExists();
    ofstream outFile(getUserRentalFile(username));

    if (!outFile.is_open()) {
        return false;
    }

    RentalNode* current = rentals;

    while (current != NULL) {
        outFile << current->data.equipment << ","
                << current->data.totalCost << ","
                << current->data.returned << endl;

        current = current->next;
    }

    return true;
}

EquipmentNode* findEquipment(EquipmentNode* equipments, string equipmentName) {
    EquipmentNode* current = equipments;

    while (current != NULL) {
        if (current->data.name == equipmentName) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void displayRental(Rental rental) {
    cout << "Equipment: " << rental.equipment << endl;
    cout << fixed << setprecision(2);
    cout << "Total Cost: " << rental.totalCost << endl;
    cout << "Status: " << (rental.returned == 1 ? "Returned" : "Not Returned") << endl;
}

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
