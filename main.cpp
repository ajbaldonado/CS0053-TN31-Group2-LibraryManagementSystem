#include <iostream>
#include "LibrarySystem.h"

using namespace std;

void displayMenu() {
    std::cout << "\n=====================================\n";
    std::cout << "      LIBRARY MANAGEMENT SYSTEM      \n";
    std::cout << "=====================================\n";
    std::cout << "1. Add New Book\n";
    std::cout << "2. View All Books\n";
    std::cout << "3. Search Catalog\n";
    std::cout << "4. Update Book Details\n";
    std::cout << "5. Remove Book\n";
    std::cout << "6. Borrow Book\n";
    std::cout << "7. Return Book\n";
    std::cout << "8. Generate Summary Report\n";
    std::cout << "9. Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Enter choice (1-9): ";
}

int main() {
    loadFromFile();
    loadUsersFromFile();

    // Authenticate user before entering the main catalog menu
    int authChoice = 0;
    while (currentUser == nullptr) {
        cout << "\n--- ACCOUNT ACCESS ---\n";
        cout << "1. Login\n";
        cout << "2. Register New User\n";
        cout << "3. Exit\n";
        cout << "Enter choice (1-3): ";

        if (!(cin >> authChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (authChoice == 1) {
            loginUser();
        } else if (authChoice == 2) {
            registerUser();
        } else if (authChoice == 3) {
            cout << "Exiting system...\n";
            return 0;
        } else {
            cout << "Please input a valid choice.\n";
        }
    }

    int choice;
    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                if (currentUser->role != "admin") { // only the admin can add books
                    cout << "[Access Denied] Admin privileges required.\n";
                    break;
                }
                addBook();
                saveToFile();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                if (currentUser->role != "admin") { // only the admin can update books
                    cout << "[Access Denied] Admin privileges required.\n";
                    break;
                }
                updateBook();
                saveToFile();
                break;
            case 5:
                if (currentUser->role != "admin") { // only the admin can remove books
                    cout << "[Access Denied] Admin privileges required.\n";
                    break;
                }
                removeBook();
                saveToFile();
                break;
            case 6:
                borrowBook();
                saveToFile();
                break;
            case 7:
                returnBook();
                saveToFile();
                break;
            case 8:
                generateSummary();
                break;
            case 9:
                saveToFile();
                saveUsersToFile();
                cout << "Saving changes and exiting system...\n"; // saves all changes to files before exiting
                break;
            default:
                cout << "Please input a valid choice.\n";
        }
    } while (choice != 9);

    return 0;
}