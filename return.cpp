#include "sportsRental.h"

void returnEquipment(string username)
{
    RentalNode* rentals = loadRentals(username);
    RentalNode* selectedRental = NULL;

    int choice;
    int activeCount = 0;

    cout << "===== Active Rentals =====" << endl;

    RentalNode* current = rentals;
    while (current != NULL)
    {
        if (current->data.returned == 0)
        {
            activeCount++;

            cout << activeCount << "." << endl;
            displayRental(current->data);
            cout << "------------------------" << endl;
        }

        current = current->next;
    }

    if (activeCount == 0)
    {
        deleteRentalList(rentals);
        showError("You have no active rentals to return.");
        return;
    }

    readInt("Choose rental to mark as returned: ", choice);

    if (choice < 1 || choice > activeCount)
    {
        deleteRentalList(rentals);
        showError("Invalid choice.");
        return;
    }

    current = rentals;
    activeCount = 0;

    while (current != NULL)
    {
        if (current->data.returned == 0)
        {
            activeCount++;

            if (activeCount == choice)
            {
                selectedRental = current;
                break;
            }
        }

        current = current->next;
    }

    EquipmentNode* equipments = loadEquipments();
    EquipmentNode* equipment = findEquipment(equipments, selectedRental->data.equipment);

    if (equipment == NULL)
    {
        deleteRentalList(rentals);
        deleteEquipmentList(equipments);
        showError("Unable to find equipment record.");
        return;
    }

    selectedRental->data.returned = 1;
    equipment->data.quantity++;

    if (!saveEquipments(equipments) || !saveRentals(username, rentals))
    {
        deleteRentalList(rentals);
        deleteEquipmentList(equipments);
        showError("Unable to save return.");
        return;
    }

    deleteRentalList(rentals);
    deleteEquipmentList(equipments);

    showMessage("Equipment marked as returned.");
}