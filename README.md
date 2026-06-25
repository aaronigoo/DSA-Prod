# Project Plan

**Sports Equipment Rental System**

## Goal

Develop a console-based C++ application where users can:

* Create an account
* Log in
* View sports equipment
* Reserve equipment
* Modify reservation schedules
* Cancel reservations
* View reservation records


# System Modules

## Module 1: User Authentication

### Features

* Sign Up
* Log In
* Log Out

### Stored Information

```text
Username
Password
```

### File

```text
users.txt
```

### Example

```text
aaron,password123
juan,qwerty
```

### Functions

```cpp
void registerUser();
bool loginUser();
```

---

## Module 2: Equipment Management

### Features

* View available equipment
* Search equipment
* Check availability

### Equipment Information

```text
Equipment ID
Equipment Name
Quantity Available
```

### Example

```text
001 Basketball 10
002 Volleyball 8
003 Tennis Racket 5
```

### File

```text
equipment.txt
```

### Structure

```cpp
struct Equipment
{
    int id;
    string name;
    int quantity;
};
```

---

## Module 3: Reservation Management

This is the heart of the system.

### Features

* Reserve equipment
* View reservations
* Change reservation time
* Cancel reservation

### Reservation Information

```text
Reservation ID
Username
Equipment ID
Date
Start Time
End Time
```

### File

```text
reservations.txt
```

### Class

```cpp
class Reservation
{
private:
    int reservationID;
    string username;
    int equipmentID;
    string date;
    string startTime;
    string endTime;
};
```

---

# Using Linked Lists

Instead of storing reservations in arrays:

```cpp
struct ReservationNode
{
    Reservation data;
    ReservationNode* next;
};
```

The linked list will:

* Load reservations from file
* Add new reservations
* Delete reservations
* Update reservations
* Display reservations

This gives a practical use of linked lists.

---

# Reservation Rules

### Rule 1

Equipment quantity cannot go below zero.

Example:

```text
Basketball Quantity = 5

5 reservations allowed.
```

---

### Rule 2

Prevent time conflicts.

Example:

```text
Basketball
June 30
1 PM - 3 PM
```

If another user tries:

```text
Basketball
June 30
2 PM - 4 PM
```

System displays:

```text
Time slot unavailable.
```

---

### Rule 3

Only the owner can modify their reservation.

---

# Suggested Menus

## Main Menu

```text
===== SPORTS EQUIPMENT RENTAL =====

1. Sign Up
2. Log In
3. Exit
```

---

## User Menu

```text
===== USER MENU =====

1. View Equipment
2. Reserve Equipment
3. View My Reservations
4. Change Reservation Time
5. Cancel Reservation
6. Logout
```

---

# File Organization (ADT / 3-File Program)

### sportsRental.h

Contains:

```cpp
Classes
Structures
Function Prototypes
```

---

### sportsRental.cpp

Contains:

```cpp
All function definitions
Linked list operations
File handling operations
```

---

### main.cpp

Contains:

```cpp
Menus
Program flow
User interaction
```

---

# Minimum Viable Version (Recommended)

If your group is short on time, implement these first:

✅ Sign Up/Login

✅ View Equipment

✅ Reserve Equipment

✅ View Reservations

✅ Change Reservation Time

✅ Cancel Reservation

✅ Save and Load Data from Files

✅ Linked List for Reservations

Once that works, you can always add stacks, queues, or trees later as bonus features if your instructor requires demonstrating those topics. This approach keeps the project manageable while still showing proper use of classes, structures, linked lists, file handling, and ADTs.
