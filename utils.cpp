#include "sportsRental.h"
#include <direct.h>

const string EQUIPMENT_FILE = "files/equipments";
const string RENTAL_FOLDER = "files/rentals";

// Parent: utils.cpp
// Function: Converts text into an integer.
// How it works: Uses stringstream and succeeds only when the whole text is a valid number.
bool toInt(string text, int &value) {
    stringstream stream(text);
    stream >> value;
    return !stream.fail() && stream.eof();
}

// Parent: utils.cpp
// Function: Converts text into a decimal number.
// How it works: Uses stringstream and succeeds only when the whole text is a valid double.
bool toDouble(string text, double &value) {
    stringstream stream(text);
    stream >> value;
    return !stream.fail() && stream.eof();
}

// Parent: utils.cpp
// Function: Checks if text contains a comma.
// How it works: Searches the string because commas are used as separators in the files.
bool containsComma(string text) {
    return text.find(',') != string::npos;
}

// Parent: utils.cpp
// Function: Clears the console screen.
// How it works: Runs the Windows cls command.
void clearScreen() {
    system("cls");
}

// Parent: utils.cpp
// Function: Pauses the program until the user presses Enter.
// How it works: Displays a message and reads one line from input.
void pauseScreen() {
    string line;

    cout << endl << "Press Enter to continue...";
    getline(cin, line);
}

// Parent: utils.cpp
// Function: Shows a normal message and pauses.
// How it works: Prints the message, then calls pauseScreen().
void showMessage(string message) {
    cout << message << endl;
    pauseScreen();
}

// Parent: utils.cpp
// Function: Shows an error message and pauses.
// How it works: Prints the error text, then calls pauseScreen().
void showError(string message) {
    cout << message << endl;
    pauseScreen();
}

// Parent: utils.cpp
// Function: Reads one whole-number input attempt.
// How it works: Parses one line with stringstream and rejects extra characters.
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

// Parent: utils.cpp
// Function: Keeps asking until the user enters a whole number.
// How it works: Repeats readIntOnce() until it returns true.
void readInt(string prompt, int &value) {
    while (true) {
        if (readIntOnce(prompt, value)) {
            return;
        }
    }
}

// Parent: utils.cpp
// Function: Reads text input from the user.
// How it works: Shows a prompt and stores the full input line.
void readText(string prompt, string &value) {
    cout << prompt;
    getline(cin >> ws, value);
}

// Parent: utils.cpp
// Function: Adds equipment data to the end of an equipment linked list.
// How it works: Creates a new node and updates head and tail pointers.
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

// Parent: utils.cpp
// Function: Adds rental data to the end of a rental linked list.
// How it works: Creates a new node and updates head and tail pointers.
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

// Parent: utils.cpp
// Function: Frees all equipment nodes from memory.
// How it works: Walks through the linked list and deletes each node.
void deleteEquipmentList(EquipmentNode* head) {
    while (head != NULL) {
        EquipmentNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}

// Parent: utils.cpp
// Function: Frees all rental nodes from memory.
// How it works: Walks through the linked list and deletes each node.
void deleteRentalList(RentalNode* head) {
    while (head != NULL) {
        RentalNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}

// Parent: utils.cpp
// Function: Loads equipment records from the equipment file.
// How it works: Reads each comma-separated line and stores valid records in a linked list.
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

// Parent: utils.cpp
// Function: Saves equipment records back to the equipment file.
// How it works: Traverses the equipment linked list and writes each node as one line.
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

// Parent: utils.cpp
// Function: Makes sure the rentals folder exists.
// How it works: Calls _mkdir; if the folder already exists, the program can continue.
void ensureRentalFolderExists() {
    _mkdir(RENTAL_FOLDER.c_str());
}

// Parent: utils.cpp
// Function: Builds the rental file path for one user.
// How it works: Combines the rentals folder path with the username.
string getUserRentalFile(string username) {
    return RENTAL_FOLDER + "/" + username;
}

// Parent: utils.cpp
// Function: Loads one user's rental records.
// How it works: Reads the user's rental file and stores valid records in a linked list.
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

// Parent: utils.cpp
// Function: Saves one user's rental records.
// How it works: Creates the rentals folder, then writes each rental node to the user's file.
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

// Parent: utils.cpp
// Function: Finds equipment by name.
// How it works: Walks through the equipment linked list and returns the matching node.
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

// Parent: utils.cpp
// Function: Displays one rental record.
// How it works: Prints the equipment, cost, and returned status from the rental data.
void displayRental(Rental rental) {
    cout << "Equipment: " << rental.equipment << endl;
    cout << fixed << setprecision(2);
    cout << "Total Cost: " << rental.totalCost << endl;
    cout << "Status: " << (rental.returned == 1 ? "Returned" : "Not Returned") << endl;
}
