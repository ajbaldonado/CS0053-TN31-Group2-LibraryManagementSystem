#include <iostream>
#include <vector>
#include <iomanip>
#include "LibrarySystem.h"

using namespace std;

vector<Book> libraryCatalog;

void addBook() {
    string title, author;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);

    int newId = libraryCatalog.empty() ? 1 : libraryCatalog.back().id + 1;
    Book newBook(newId, title, author);
    libraryCatalog.push_back(newBook);
    cout << "Book added successfully with ID: " << newId << endl;
};

void removeBook() {
};

void updateBook() {
};

void viewAllBooks() {
};