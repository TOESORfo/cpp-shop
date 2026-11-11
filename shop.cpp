
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

vector<Product> inventory;

int findProduct(int id) {
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addProduct() {
    Product p;

    cout << "\nProduct ID: ";
    cin >> p.id;

    if (findProduct(p.id) != -1) {
        cout << "Product ID already exists!\n";
        return;
    }

    cout << "Product name: ";
    getline(cin >> ws, p.name);

    cout << "Price: ";
    cin >> p.price;

    cout << "Quantity: ";
    cin >> p.quantity;

    if (p.price < 0 || p.quantity < 0) {
        cout << "Invalid price or quantity!\n";
        return;
    }

    inventory.push_back(p);

    cout << "Product added successfully!\n";
}

void viewInventory() {
    if (inventory.empty()) {
        cout << "\nInventory is empty.\n";
        return;
    }

    cout << "\n"
         << left << setw(8) << "ID"
         << setw(20) << "Name"
         << setw(12) << "Price"
         << "Quantity\n";

    cout << "------------------------------------------------\n";

    for (const Product& p : inventory) {
        cout << left << setw(8) << p.id
             << setw(20) << p.name
             << setw(12) << fixed << setprecision(2) << p.price
             << p.quantity << "\n";
    }
}

void removeProduct() {
    int id;

    cout << "\nEnter product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    inventory.erase(inventory.begin() + index);

    cout << "Product removed successfully!\n";
}

void searchProduct() {
    int id;

    cout << "\nEnter product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    Product p = inventory[index];

    cout << "\nName: " << p.name;
    cout << "\nPrice: " << p.price;
    cout << "\nQuantity: " << p.quantity << "\n";
}

void editProduct() {
    int id;

    cout << "\nEnter product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    Product& p = inventory[index];

    cout << "New name: ";
    getline(cin >> ws, p.name);

    cout << "New price: ";
    cin >> p.price;

    cout << "New quantity: ";
    cin >> p.quantity;

    if (p.price < 0 || p.quantity < 0) {
        cout << "Invalid values! Changes were applied, so edit again.\n";
        return;
    }

    cout << "Product updated!\n";
}

void sellProduct() {
    int id, amount;

    cout << "\nEnter product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Amount to sell: ";
    cin >> amount;

    if (amount <= 0 || amount > inventory[index].quantity) {
        cout << "Invalid amount or insufficient stock!\n";
        return;
    }

    inventory[index].quantity -= amount;

    double total = amount * inventory[index].price;

    cout << "Sale successful!\n";
    cout << "Total: $" << fixed << setprecision(2) << total << "\n";
}

void lowStockReport() {
    cout << "\nLOW STOCK PRODUCTS\n";

    bool found = false;

    for (const Product& p : inventory) {
        if (p.quantity <= 5) {
            cout << p.name << " - " << p.quantity << " left\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No products running low.\n";
    }
}

void saveInventory() {
    ofstream file("inventory.txt");

    if (!file) {
        cout << "Could not save inventory!\n";
        return;
    }

    for (const Product& p : inventory) {
        file << p.id << "\n"
             << p.name << "\n"
             << p.price << "\n"
             << p.quantity << "\n";
    }

    cout << "Inventory saved!\n";
}

void loadInventory() {
    ifstream file("inventory.txt");

    if (!file) return;

    inventory.clear();

    Product p;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);

        if (!(file >> p.price >> p.quantity)) {
            inventory.clear();
            cout << "Inventory file is corrupted!\n";
            return;
        }

        inventory.push_back(p);
    }
}

int main() {
    loadInventory();

    int choice;

    do {
        cout << "\n_________________________________\n";
        cout << "       INVENTORY MANAGER\n";
        cout << "_________________________________\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Edit Product\n";
        cout << "4. View Inventory\n";
        cout << "5. Search Product\n";
        cout << "6. Sell Product\n";
        cout << "7. Low Stock Report\n";
        cout << "8. Save Inventory\n";
        cout << "9. Exit\n";
        cout << "______________________________\n";
        cout << "Select an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: editProduct(); break;
            case 4: viewInventory(); break;
            case 5: searchProduct(); break;
            case 6: sellProduct(); break;
            case 7: lowStockReport(); break;
            case 8: saveInventory(); break;
            case 9:
                saveInventory();
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

    } while (choice != 9);

    return 0;
}
