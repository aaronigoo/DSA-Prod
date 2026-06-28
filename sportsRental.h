#ifndef SPORTSRENTAL_H
#define SPORTSRENTAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>
#include <queue>
#include <stack>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// ======================================================
// CLASSES
// ======================================================

struct user {
    string username;
    string password;
};

struct Equipment {
    string name;
    int quantity;
    double ratePerDay;
};

struct Rental {
    string equipment;
    double totalCost;
    int returned;
};

struct EquipmentNode {
    Equipment data;
    EquipmentNode* next;
};

struct RentalNode {
    Rental data;
    RentalNode* next;
};

// ======================================================
// UTIL FUNCTIONS
// ======================================================

bool toInt(string text, int &value);
bool toDouble(string text, double &value);
bool containsComma(string text);
void readInt(string prompt, int &value);
bool readIntOnce(string prompt, int &value);
void readText(string prompt, string &value);
void clearScreen();
void pauseScreen();
void showMessage(string message);
void showError(string message);
void addEquipmentNode(EquipmentNode* &head, EquipmentNode* &tail, Equipment equipment);
void addRentalNode(RentalNode* &head, RentalNode* &tail, Rental rental);
void deleteEquipmentList(EquipmentNode* head);
void deleteRentalList(RentalNode* head);
EquipmentNode* loadEquipments();
bool saveEquipments(EquipmentNode* equipments);
void ensureRentalFolderExists();
string getUserRentalFile(string username);
RentalNode* loadRentals(string username);
bool saveRentals(string username, RentalNode* rentals);
EquipmentNode* findEquipment(EquipmentNode* equipments, string equipmentName);
void displayRental(Rental rental);

// ======================================================
// DISPLAY FUNCTIONS
// ======================================================

void displayAuth();
void displayMenu(string user);

// ======================================================
// AUTHENTICATION FUNCTIONS
// ======================================================

void signUp();
int logIn(string &user);
void forgotPassword();
int getUser(string &user);
void logOut();

// ======================================================
// RENTAL FUNCTIONS
// ======================================================

void viewEquipment();
void rentEquipment(string username);
void returnEquipment(string username);
void viewRentalHistory(string username);

#endif
