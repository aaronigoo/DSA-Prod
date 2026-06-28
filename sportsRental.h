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

void readInt(string prompt, int &value);
bool readIntOnce(string prompt, int &value);
void readText(string prompt, string &value);
void clearScreen();
void pauseScreen();
void showMessage(string message);
void showError(string message);

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
