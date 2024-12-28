#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h> // For Sleep function

using namespace std;

struct GroceryItem {
    string name;
    float price;
    int quantity;
};

void clearScreen() {
    system("cls"); // Clear screen for Windows
}

void pause(int seconds) {
    Sleep(seconds * 1000); // Convert seconds to milliseconds
}

void displayInventory(GroceryItem inventory[], int size) {
    clearScreen();
    cout << "===================================" << endl;
    cout << "         Inventory List            " << endl;
    cout << "===================================" << endl;
    if (size == 0) {
        cout << "Inventory is empty!" << endl;
    } else {
        cout << left << setw(20) << "Item"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;
        cout << "-----------------------------------" << endl;
        for (int i = 0; i < size; ++i) {
            cout << left << setw(20) << inventory[i].name
                 << "$" << setw(9) << inventory[i].price
                 << inventory[i].quantity << endl;
        }
    }
    cout << "===================================" << endl;
    cout << "\nPress Enter to continue...";
    cin.ignore(); 
    cin.get();    
}

void addItem(GroceryItem inventory[], int &size, int max_size) {
    clearScreen();
    if (size >= max_size) {
        cout << "Inventory is full!" << endl;
        return;
    }

    string name;
    float price;
    int quantity;

    cout << "Enter the item name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter the price of " << name << ": $";
    cin >> price;
    cout << "Enter the quantity of " << name << ": ";
    cin >> quantity;

    inventory[size].name = name;
    inventory[size].price = price;
    inventory[size].quantity = quantity;

    size++;
    cout << name << " has been added to the inventory." << endl;
    pause(2); // Pause for 2 seconds
}

void updateItemQuantity(GroceryItem inventory[], int size, string name, int new_quantity) {
    clearScreen();
    for (int i = 0; i < size; ++i) {
        if (inventory[i].name == name) {
            inventory[i].quantity = new_quantity;
            cout << "The quantity of " << name << " has been updated to " << new_quantity << endl;
            pause(2);
            return;
        }
    }
    cout << "Item not found!" << endl;
    pause(2);
}

void removeItem(GroceryItem inventory[], int &size, string name) {
    clearScreen();
    for (int i = 0; i < size; ++i) {
        if (inventory[i].name == name) {
            for (int j = i; j < size - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            size--;
            cout << name << " has been removed from the inventory." << endl;
            pause(2);
            return;
        }
    }
    cout << "Item not found!" << endl;
    pause(2);
}

int main() {
    const int MAX_ITEMS = 100;
    GroceryItem inventory[MAX_ITEMS];
    int inventory_size = 0;

    int choice;
    do {
        clearScreen();
        cout << "===================================" << endl;
        cout << "       Grocery Inventory System    " << endl;
        cout << "===================================" << endl;
        cout << "1. Display Inventory" << endl;
        cout << "2. Add Item" << endl;
        cout << "3. Update Item Quantity" << endl;
        cout << "4. Remove Item" << endl;
        cout << "5. Exit" << endl;
        cout << "===================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayInventory(inventory, inventory_size);
                break;
            case 2:
                addItem(inventory, inventory_size, MAX_ITEMS);
                break;
            case 3: {
                string item_name;
                int new_quantity;
                cout << "Enter the item name to update: ";
                cin.ignore();
                getline(cin, item_name);
                cout << "Enter the new quantity for " << item_name << ": ";
                cin >> new_quantity;
                updateItemQuantity(inventory, inventory_size, item_name, new_quantity);
                break;
            }
            case 4: {
                string item_name;
                cout << "Enter the item name to remove: ";
                cin.ignore();
                getline(cin, item_name);
                removeItem(inventory, inventory_size, item_name);
                break;
            }
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pause(2);
                break;
        }
    } while (choice != 5);

    return 0;
}
