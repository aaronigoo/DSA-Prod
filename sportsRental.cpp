#include "sportsRental.h"

// ======================================================
// RENTAL FUNCTIONS ONLY
// ======================================================

const string EQUIPMENT_FILE = "files/equipments";
const string RENTAL_FILE = "files/rentals";

vector<string> splitLine(string line) {
    vector<string> parts;
    string part;
    stringstream stream(line);

    while (getline(stream, part, ',')) {
        parts.push_back(part);
    }

    return parts;
}

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

int daysInMonth(int month) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12) {
        return 0;
    }

    return days[month];
}

bool validDate(int month, int day) {
    return month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth(month);
}

int dayOfYear(int month, int day) {
    int total = day;

    for (int currentMonth = 1; currentMonth < month; currentMonth++) {
        total += daysInMonth(currentMonth);
    }

    return total;
}

int rentalDays(int startMonth, int startDay, int endMonth, int endDay) {
    int start = dayOfYear(startMonth, startDay);
    int end = dayOfYear(endMonth, endDay);

    return end - start + 1;
}

bool dateRangesOverlap(Rental rental, int startMonth, int startDay, int endMonth, int endDay) {
    int rentalStart = dayOfYear(rental.startMonth, rental.startDay);
    int rentalEnd = dayOfYear(rental.endMonth, rental.endDay);
    int requestedStart = dayOfYear(startMonth, startDay);
    int requestedEnd = dayOfYear(endMonth, endDay);

    return rentalStart <= requestedEnd && requestedStart <= rentalEnd;
}

vector<Equipment> loadEquipments() {
    vector<Equipment> equipments;
    ifstream inFile(EQUIPMENT_FILE);
    string line;

    while (getline(inFile, line)) {
        vector<string> parts = splitLine(line);
        Equipment equipment;

        if (parts.size() != 3) {
            continue;
        }

        equipment.name = parts[0];

        if (!toInt(parts[1], equipment.quantity) || !toDouble(parts[2], equipment.ratePerDay)) {
            continue;
        }

        if (!equipment.name.empty() && equipment.quantity > 0 && equipment.ratePerDay >= 0) {
            equipments.push_back(equipment);
        }
    }

    return equipments;
}

vector<Rental> loadRentals() {
    vector<Rental> rentals;
    ifstream inFile(RENTAL_FILE);
    string line;

    while (getline(inFile, line)) {
        vector<string> parts = splitLine(line);
        Rental rental;

        if (parts.size() != 8) {
            continue;
        }

        rental.username = parts[0];
        rental.equipment = parts[1];

        if (!toDouble(parts[2], rental.totalCost) ||
            !toInt(parts[3], rental.startMonth) ||
            !toInt(parts[4], rental.startDay) ||
            !toInt(parts[5], rental.endMonth) ||
            !toInt(parts[6], rental.endDay) ||
            !toInt(parts[7], rental.returned)) {
            continue;
        }

        if (!rental.username.empty() && !rental.equipment.empty()) {
            rentals.push_back(rental);
        }
    }

    return rentals;
}

void saveRentals(vector<Rental> rentals) {
    ofstream outFile(RENTAL_FILE);

    for (size_t index = 0; index < rentals.size(); index++) {
        outFile << rentals[index].username << ","
                << rentals[index].equipment << ","
                << rentals[index].totalCost << ","
                << rentals[index].startMonth << ","
                << rentals[index].startDay << ","
                << rentals[index].endMonth << ","
                << rentals[index].endDay << ","
                << rentals[index].returned << endl;
    }
}

int findEquipment(vector<Equipment> equipments, string equipmentName) {
    for (size_t index = 0; index < equipments.size(); index++) {
        if (equipments[index].name == equipmentName) {
            return static_cast<int>(index);
        }
    }

    return -1;
}

int countOverlappingActiveRentals(vector<Rental> rentals, string equipmentName, int startMonth, int startDay, int endMonth, int endDay) {
    int count = 0;

    for (size_t index = 0; index < rentals.size(); index++) {
        if (rentals[index].equipment == equipmentName &&
            rentals[index].returned == 0 &&
            dateRangesOverlap(rentals[index], startMonth, startDay, endMonth, endDay)) {
            count++;
        }
    }

    return count;
}

void displayRental(Rental rental) {
    cout << "Equipment: " << rental.equipment << endl;
    cout << "Date: " << rental.startMonth << "/" << rental.startDay
         << " to " << rental.endMonth << "/" << rental.endDay << endl;
    cout << fixed << setprecision(2);
    cout << "Total Cost: " << rental.totalCost << endl;
    cout << "Status: " << (rental.returned == 1 ? "Returned" : "Not Returned") << endl;
}

void viewEquipment() {
    vector<Equipment> equipments = loadEquipments();

    if (equipments.empty()) {
        showError("No equipment records found.");
        return;
    }

    cout << "===== AVAILABLE EQUIPMENT =====" << endl;
    cout << fixed << setprecision(2);

    for (size_t index = 0; index < equipments.size(); index++) {
        cout << "[" << index + 1 << "] "
             << equipments[index].name
             << " | Quantity: " << equipments[index].quantity
             << " | Rate per day: " << equipments[index].ratePerDay
             << endl;
    }
}

void rentEquipment(string username) {
    vector<Equipment> equipments = loadEquipments();
    vector<Rental> rentals = loadRentals();
    string equipmentName;
    int startMonth;
    int startDay;
    int endMonth;
    int endDay;

    if (equipments.empty()) {
        showError("No equipment available for rental.");
        return;
    }

    viewEquipment();
    cout << "Enter equipment name: ";
    getline(cin, equipmentName);

    if (containsComma(equipmentName)) {
        showError("Equipment name cannot contain commas.");
        return;
    }

    int equipmentIndex = findEquipment(equipments, equipmentName);

    if (equipmentIndex == -1) {
        showError("Equipment not found.");
        return;
    }

    readInt("Enter rental start month: ", startMonth);
    readInt("Enter rental start day: ", startDay);
    readInt("Enter return month: ", endMonth);
    readInt("Enter return day: ", endDay);

    if (!validDate(startMonth, startDay) || !validDate(endMonth, endDay)) {
        showError("Invalid date.");
        return;
    }

    int numberOfDays = rentalDays(startMonth, startDay, endMonth, endDay);

    if (numberOfDays < 1) {
        showError("Return date cannot be before rental date.");
        return;
    }

    int rentedCount = countOverlappingActiveRentals(rentals, equipmentName, startMonth, startDay, endMonth, endDay);

    if (rentedCount >= equipments[equipmentIndex].quantity) {
        showError("Equipment is not available for that timeframe.");
        return;
    }

    Rental rental;
    rental.username = username;
    rental.equipment = equipmentName;
    rental.totalCost = numberOfDays * equipments[equipmentIndex].ratePerDay;
    rental.startMonth = startMonth;
    rental.startDay = startDay;
    rental.endMonth = endMonth;
    rental.endDay = endDay;
    rental.returned = 0;

    ofstream outFile(RENTAL_FILE, ios::app);

    if (!outFile.is_open()) {
        showError("Unable to open rentals file.");
        return;
    }

    outFile << rental.username << ","
            << rental.equipment << ","
            << rental.totalCost << ","
            << rental.startMonth << ","
            << rental.startDay << ","
            << rental.endMonth << ","
            << rental.endDay << ","
            << rental.returned << endl;

    cout << fixed << setprecision(2);
    cout << "Rental successful. Total cost: " << rental.totalCost << endl;
    pauseScreen();
}

void returnEquipment(string username) {
    vector<Rental> rentals = loadRentals();
    vector<int> activeRentalIndexes;
    int choice;

    cout << "===== ACTIVE RENTALS =====" << endl;

    for (size_t index = 0; index < rentals.size(); index++) {
        if (rentals[index].username == username && rentals[index].returned == 0) {
            activeRentalIndexes.push_back(static_cast<int>(index));
            cout << "[" << activeRentalIndexes.size() << "]" << endl;
            displayRental(rentals[index]);
            cout << "--------------------------" << endl;
        }
    }

    if (activeRentalIndexes.empty()) {
        showError("You have no active rentals to return.");
        return;
    }

    readInt("Choose rental to mark as returned: ", choice);

    if (choice < 1 || choice > static_cast<int>(activeRentalIndexes.size())) {
        showError("Invalid choice.");
        return;
    }

    rentals[activeRentalIndexes[choice - 1]].returned = 1;
    saveRentals(rentals);
    showMessage("Equipment marked as returned.");
}

void viewRentalHistory(string username) {
    vector<Rental> rentals = loadRentals();
    queue<Rental> rentalQueue;
    stack<Rental> rentalStack;
    int choice;

    for (size_t index = 0; index < rentals.size(); index++) {
        if (rentals[index].username == username) {
            rentalQueue.push(rentals[index]);
            rentalStack.push(rentals[index]);
        }
    }

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
