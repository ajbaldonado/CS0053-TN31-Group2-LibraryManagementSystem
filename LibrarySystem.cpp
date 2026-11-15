#include <iostream>
#include <vector>
#include <iomanip>
#include "LibrarySystem.h"

using namespace std;

vector<Book> libraryCatalog;

void addBook() {
};

void removeBook() {
};

void updateBook() {
};

void viewAllBooks(const vector<Book>& libraryCatalog) {
    for (const auto& book : libraryCatalog) {
        cout << "[" << book.id << "] " << book.title << " by " << book.author << " — ";
        
        if (book.isAvailable) {
            cout << "Available\n";
        } else {
            cout << "Borrowed\n";
        }
    }
};
