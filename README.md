# Sports Equipment Rental System

This is a console-based C++ sports equipment rental system. Users can sign up, log in, rent equipment for one day, return equipment, and view their rental history.

The project now uses linked lists with pointers instead of vectors. Rental records are stored separately per user inside the `files/rentals` folder, and equipment availability is tracked by changing the quantity inside `files/equipments`.

## Current Data Files

### `files/users`

Stores user accounts. Each line contains a username and password separated by a comma.

### `files/userdata`

Stores the currently logged-in username so the program can remember the login session.

### `files/equipments`

Stores equipment records. Each line contains the equipment name, available quantity, and one-day rental rate.

### `files/rentals/{username}`

Stores rental records for one user only. Each line contains the equipment name, total cost, and returned status.

## Important Rules

### One-Day Rentals

All rentals are treated as one-day rentals. The system no longer asks for start dates, return dates, or times.

### Equipment Availability

When a user rents equipment, the equipment quantity decreases by one. When a user returns equipment, the quantity increases by one.

### Per-User Rental Files

The program reads only the current user's rental file when showing history or returning equipment. It does not scan other users' rental files.

### Username Safety

Usernames cannot be empty and cannot contain commas or file path characters. This keeps usernames safe to use as rental file names.

# File Organization

## `sportsRental.h`

This header contains the shared structures and function prototypes used by all `.cpp` files.

### `struct user`

Stores a username and password.

### `struct Equipment`

Stores one equipment record: equipment name, available quantity, and rate per day.

### `struct Rental`

Stores one simplified rental record: equipment name, total cost, and returned status.

### `struct EquipmentNode`

Stores one `Equipment` item inside a linked list. The `next` pointer connects it to the next equipment node.

### `struct RentalNode`

Stores one `Rental` item inside a linked list. The `next` pointer connects it to the next rental node.

# `main.cpp`

Handles the main program loop and menu navigation.

## `main()`

Starts the program, checks if a user is already logged in, and repeatedly shows either the authentication menu or the user menu. It calls the correct function based on the user's menu choice.

# `display.cpp`

Contains functions that print menus.

## `displayAuth()`

Displays the sign up, log in, forgot password, and exit menu for users who are not logged in.

## `displayMenu(string user)`

Displays the main user menu after login. It shows the current username and the choices for renting, returning, viewing history, logging out, or exiting.

# `auth.cpp`

Contains account and login-related functions.

## `hasComma(string text)`

Checks whether text contains a comma. This matters because the users file uses commas to separate usernames and passwords.

## `hasUnsafeUsernameCharacter(string username)`

Checks whether a username contains characters that are unsafe for file names, such as slashes, colons, quotes, or angle brackets.

## `isValidUsername(string username)`

Checks whether a username is not empty and does not contain unsafe characters.

## `findUser(string username, string &password)`

Searches the users file for a matching username. If found, it stores that user's password in the password reference and returns true.

## `signUp()`

Creates a new user account. It reads a username and password, validates them, checks for duplicate usernames, and appends the new account to the users file.

## `logIn(string &user)`

Logs in an existing user. It checks the entered username and password against the users file, saves the login session to `files/userdata`, and updates the current user variable.

## `forgotPassword()`

Lets a user recover their password by entering their username. If the username exists, the saved password is displayed.

## `getUser(string &user)`

Checks `files/userdata` to see if someone is already logged in. If a username is found, it loads that username into the user variable.

## `logOut()`

Logs the user out by deleting the `files/userdata` session file.

# `utils.cpp`

Contains shared helper functions used by the other files.

## `toInt(string text, int &value)`

Converts text into an integer. It uses a string stream and only succeeds if the whole text is a valid whole number.

## `toDouble(string text, double &value)`

Converts text into a decimal number. It uses a string stream and only succeeds if the whole text is a valid number.

## `containsComma(string text)`

Checks whether text contains a comma. This is used to prevent file format problems.

## `clearScreen()`

Clears the console screen by running the Windows `cls` command.

## `pauseScreen()`

Pauses the program until the user presses Enter.

## `showMessage(string message)`

Displays a normal message and then pauses the screen.

## `showError(string message)`

Displays an error message and then pauses the screen.

## `readIntOnce(string prompt, int &value)`

Tries to read one whole number from the user. It rejects invalid input and extra characters.

## `readInt(string prompt, int &value)`

Keeps asking until the user enters a valid whole number.

## `readText(string prompt, string &value)`

Displays a prompt and reads a full line of text from the user.

## `addEquipmentNode(EquipmentNode* &head, EquipmentNode* &tail, Equipment equipment)`

Adds one equipment record to the end of an equipment linked list. It updates both the head and tail pointers when needed.

## `addRentalNode(RentalNode* &head, RentalNode* &tail, Rental rental)`

Adds one rental record to the end of a rental linked list. It updates both the head and tail pointers when needed.

## `deleteEquipmentList(EquipmentNode* head)`

Deletes every node in an equipment linked list to free memory.

## `deleteRentalList(RentalNode* head)`

Deletes every node in a rental linked list to free memory.

## `loadEquipments()`

Reads all valid equipment records from `files/equipments` and stores them in an equipment linked list.

## `saveEquipments(EquipmentNode* equipments)`

Writes the equipment linked list back into `files/equipments`. This is used after renting or returning equipment.

## `ensureRentalFolderExists()`

Makes sure the `files/rentals` folder exists before the program reads or writes user rental files.

## `getUserRentalFile(string username)`

Builds the file path for the current user's rental file.

## `loadRentals(string username)`

Reads one user's rental file and stores the records in a rental linked list.

## `saveRentals(string username, RentalNode* rentals)`

Writes one user's rental linked list back into that user's rental file.

## `findEquipment(EquipmentNode* equipments, string equipmentName)`

Searches the equipment linked list for a matching equipment name. It returns the matching node or `NULL` if the equipment is not found.

## `displayRental(Rental rental)`

Displays one rental record, including equipment name, total cost, and returned status.

# `rent.cpp`

Contains functions for viewing and renting equipment.

## `viewEquipment()`

Loads the equipment linked list, displays each equipment item, and then deletes the linked list from memory.

## `rentEquipment(string username)`

Lets the current user rent one equipment item. It checks whether the equipment exists and has available quantity, decreases the quantity by one, saves the equipment file, and appends the rental to the user's rental file.

# `return.cpp`

Contains the function for returning rented equipment.

## `returnEquipment(string username)`

Loads the current user's rentals, displays active rentals, asks which rental to return, marks it as returned, increases the equipment quantity by one, and saves both the rental file and equipment file.

# `history.cpp`

Contains the function for viewing rental history.

## `viewRentalHistory(string username)`

Loads the current user's rentals and lets the user display them from oldest to newest using a queue or newest to oldest using a stack.

# Build and Run

## VS Code

The VS Code build task compiles the current split-file version and creates `build/Debug/outDebug.exe`. The launch configuration runs that executable.

## Manual Compile Command

Run this command in the project folder:

`g++ main.cpp utils.cpp rent.cpp return.cpp history.cpp auth.cpp display.cpp -o build\Debug\outDebug.exe`

# Current Compile Files

The project currently compiles these `.cpp` files:

- `main.cpp`
- `utils.cpp`
- `rent.cpp`
- `return.cpp`
- `history.cpp`
- `auth.cpp`
- `display.cpp`

`sportsRental.cpp` has been removed because its old implementation was split into the smaller files above.
