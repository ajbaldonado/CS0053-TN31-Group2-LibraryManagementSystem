#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "LibrarySystem.h"

using namespace std;

vector<Book> libraryCatalog;

// Reads an int safely; returns false if input wasn't a number
static bool readInt(int& out) {
    if (!(cin >> out)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
    return true;
}

void addBook() { //Prompts the user to enter book details to be added into the catalog (asks for name and author).
    string title, author;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);

    if (title.empty() || author.empty()) {
        cout << "Title and author cannot be empty. Book not added.\n";
        return;
    }

    int newId = libraryCatalog.empty() ? 1 : libraryCatalog.back().id + 1;
    libraryCatalog.push_back(Book(newId, title, author));
    cout << "Book added successfully with ID: " << newId << endl;
}

void removeBook() { // Prompts the user to enter the ID of the book to be removed from the catalog.
    int id;
    cout << "Enter book ID to remove: ";
    if (!readInt(id)) {
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    auto it = find_if(libraryCatalog.begin(), libraryCatalog.end(),
                      [id](const Book& b) { return b.id == id; });
    if (it != libraryCatalog.end()) {
        libraryCatalog.erase(it);
        cout << "Book removed successfully." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

void updateBook() { // Prompts the user to enter the ID of the book to be updated.
    int id;
    cout << "Enter book ID to update: ";
    if (!readInt(id)) {
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    auto it = find_if(libraryCatalog.begin(), libraryCatalog.end(),
                      [id](const Book& b) { return b.id == id; });
    if (it == libraryCatalog.end()) {
        cout << "Book not found." << endl;
        return;
    }

    string title, author;
    cout << "Enter new book title: ";
    getline(cin, title);
    cout << "Enter new book author: ";
    getline(cin, author);

    if (title.empty() || author.empty()) {
        cout << "Title and author cannot be empty. No changes made.\n";
        return;
    }
    it->title = title;
    it->author = author;
    cout << "Book updated successfully." << endl;
}

void viewAllBooks() { // Displays all the books currently registered in the catalog in a tabular format
    if (libraryCatalog.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    cout << left << setw(6) << "ID" << setw(30) << "Title"
         << setw(25) << "Author" << "Status\n";
    cout << string(70, '-') << "\n";
    for (const auto& b : libraryCatalog) {
        cout << left << setw(6) << b.id << setw(30) << b.title
             << setw(25) << b.author
             << (b.isAvailable ? "Available" : "Borrowed") << "\n";
    }
}

void searchBook() { // Searches for books by ID, title, or author and displays the book's details
    if (libraryCatalog.empty()) {
        cout << "No books in the library to search." << endl;
        return;
    }

    string query;
    cout << "Enter ID, title, or author: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;
    cout << "\nSEARCH RESULTS\n";
    for (const auto& b : libraryCatalog) {
        if (to_string(b.id) == query || 
            b.title.find(query) != string::npos || // find + npos to allow partial keywords
            b.author.find(query) != string::npos) {
            
            cout << "ID:       " << b.id << "\n"
                 << "Title:    " << b.title << "\n"
                 << "Author:   " << b.author << "\n"
                 << "Status:   " << (b.isAvailable ? "Available" : "Borrowed") << "\n";
            /* if (!b.isAvailable) {
                cout << "Borrower: " << (b.borrower.empty() ? "Unknown" : b.borrower) << "\n";
            } */ // TEMPORARILY DISABLED
            found = true;
        }
    }
    if (!found) {
        cout << "No books found matching " << query << ".\n";
    }
}

void generateSummary() { 
    cout << "Summary feature coming soon.\n";
    
    }

void borrowBook() { cout << "Borrow feature coming soon.\n"; }
void returnBook() { cout << "Return feature coming soon.\n"; }
void loadFromFile() {}
void saveToFile() {}
