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
                addBook(); 
                break;
            case 2: 
                viewAllBooks(); 
                break;
            case 3: 
                searchBook(); 
                break;
            case 4: 
                updateBook(); 
                break;
            case 5: 
                removeBook(); 
                break;
            case 6: 
                borrowBook(); 
                break;
            case 7: 
                returnBook(); 
                break;
            case 8: 
                generateSummary(); 
                break;
            case 9:
                saveToFile();
                cout << "Saving changes and exiting system...\n";
                break;
            default:
                cout << "Please input a valid choice.\n";
        }
    } while (choice != 9);

    return 0;
}