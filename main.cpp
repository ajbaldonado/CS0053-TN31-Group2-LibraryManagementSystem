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
    std::cout << "9. View Overdue Books\n";
    std::cout << "10. Logout\n";
    std::cout << "=====================================\n";
    std::cout << "Enter choice (1-10): ";
}

void displayUserMenu() {
    std::cout << "\n=====================================\n";
    std::cout << "      LIBRARY MANAGEMENT SYSTEM      \n";
    std::cout << "=====================================\n";
    std::cout << "Logged in as: " << currentUser->username << "\n";
    std::cout << "1. View All Books\n";
    std::cout << "2. Search Catalog\n";
    std::cout << "3. Borrow Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. My Borrowed Books\n";
    std::cout << "6. Logout\n";
    std::cout << "7. Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Enter choice (1-7): ";
}

// Runs the user menu. Returns true if the program should exit, false if the user logged out.
bool runUserMenu() {
    while (true) {
        displayUserMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                viewAllBooks();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                borrowBook();
                saveToFile();
                break;
            case 4:
                returnBook();
                saveToFile();
                break;
            case 5:
                viewMyBooks();
                break;
            case 6:
                saveToFile();
                cout << "Logged out.\n";
                return false;
            case 7:
                saveToFile();
                saveUsersToFile();
                cout << "Saving changes and exiting system...\n";
                return true;
            default:
                cout << "Please input a valid choice.\n";
        }
    }
}

// Returns true if the program should exit, false if the admin logged out.
bool runAdminMenu() {
    while (true) {
        displayMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
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
                updateBook();
                saveToFile();
                break;
            case 5:
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
                viewOverdueBooks();
                break;
            case 10:
                saveToFile();
                cout << "Logged out.\n";
                return false;
            default:
                cout << "Please input a valid choice.\n";
        }
    }
}

int main() {
    loadFromFile();
    loadUsersFromFile();

    bool exitProgram = false;
    while (!exitProgram) {
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

        if (currentUser->role == "admin") {
            exitProgram = runAdminMenu();
        } else {
            exitProgram = runUserMenu();
        }
        currentUser = nullptr;
    }
        return 0;
}
