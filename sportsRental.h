#ifndef SPORTSRENTAL_H
#define SPORTSRENTAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>
using namespace std;

// ======================================================
// CLASSES
// ======================================================

struct user {
    string username;
    string password;
};

// ======================================================
// UTIL FUNCTIONS
// ======================================================



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

#endif
