#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include "LibrarySystem.h"

using namespace std;

vector<Book> libraryCatalog;
vector<User> userList;
User* currentUser = nullptr;

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

void generateSummary() { // Summarizes status of all books
    if (libraryCatalog.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    int availableCount = 0;
    int borrowedCount = 0;
    for (const auto& b : libraryCatalog) {
        if (b.isAvailable) {
            availableCount++;
        } else {
            borrowedCount++;
        }
    }
    cout << "Total Books in System:     " << libraryCatalog.size() << "\n";
    cout << "Number of Books Available: " << availableCount << "\n";
    cout << "Number of Books Borrowed:  " << borrowedCount << "\n";
}

bool loginUser() { // logins user/admin if acc exists
    string uname, pass;
    cin.ignore(10000, '\n');
    cout << "\n--- LOGIN ---\n";
    cout << "Username: ";
    getline(cin, uname);
    cout << "Password: ";
    getline(cin, pass);

    for (auto& u : userList) {
        if (u.username == uname && u.password == pass) {
            currentUser = &u;
            cout << "Login successful! Welcome, " << u.username << " [" << u.role << "].\n";
            return true;
        }
    }
    cout << "[Error] Invalid username or password.\n";
    return false;
}

void registerUser() { // creates a new user acc
    string uname, pass;
    cin.ignore(10000, '\n');
    cout << "\n--- REGISTER NEW USER ---\n";
    cout << "Enter Username: ";
    getline(cin, uname);

    if (uname.empty() || uname.find('|') != string::npos) {
        cout << "[Error] Username cannot be empty or contain '|'.\n";
        return;
    }

    for (const auto& u : userList) {
        if (u.username == uname) {
            cout << "[Error] Username already taken.\n";
            return;
        }
    }

    cout << "Enter Password: ";
    getline(cin, pass);
    if (pass.empty() || pass.find('|') != string::npos) {
        cout << "[Error] Password cannot be empty or contain '|'.\n";
        return;
    }

    int nextId = userList.empty() ? 1 : userList.back().id + 1;
    userList.push_back(User(nextId, uname, pass, "user"));
    saveUsersToFile();
    cout << "Registration successful! You can now log in.\n";
}

void loadFromFile() { // loads saved book records
    libraryCatalog.clear();
    ifstream inFile("books.txt");
    if (!inFile.is_open()) {
        return; // create file on first save
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, author, availStr, borrower, due;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, availStr, '|');
        getline(ss, borrower, '|');
        getline(ss, due, '|');

        if (idStr.empty()) continue;
        int id = stoi(idStr);
        bool isAvail = (availStr == "1");
        if (borrower.empty()) borrower = "NONE";
        if (due.empty()) due = "NONE";

        libraryCatalog.push_back(Book(id, title, author, isAvail, borrower, due));
    }
    inFile.close();
}

void saveToFile() { // saves all book records
    ofstream outFile("books.txt");
    if (!outFile.is_open()) {
        cerr << "[Error] Unable to open books.txt for saving.\n";
        return;
    }

    for (const auto& b : libraryCatalog) {
        outFile << b.id << "|"
                << b.title << "|"
                << b.author << "|"
                << (b.isAvailable ? "1" : "0") << "|"
                << b.borrowedBy << "|"
                << b.dueDate << "\n";
    }
    outFile.close();
}

void loadUsersFromFile() { // loads user/admin accounts; creates a default user and admin acc
    userList.clear();
    ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        // generate starter data on first run
        userList.push_back(User(1, "admin", "admin123", "admin"));
        userList.push_back(User(2, "student1", "pass123", "user"));
        saveUsersToFile();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, uname, pass, role;

        getline(ss, idStr, '|');
        getline(ss, uname, '|');
        getline(ss, pass, '|');
        getline(ss, role, '|');

        if (idStr.empty()) continue;
        userList.push_back(User(stoi(idStr), uname, pass, role));
    }
    inFile.close();

    if (userList.empty()) {
        userList.push_back(User(1, "admin", "admin123", "admin"));
        saveUsersToFile();
    }
}

void saveUsersToFile() { // saves all registered accs
    ofstream outFile("users.txt");
    if (!outFile.is_open()) {
        cerr << "[Error] Unable to open users.txt for saving.\n";
        return;
    }

    for (const auto& u : userList) {
        outFile << u.id << "|"
                << u.username << "|"
                << u.password << "|"
                << u.role << "\n";
    }
    outFile.close();
}

void borrowBook() { cout << "Borrow feature coming soon.\n"; }
void returnBook() { cout << "Return feature coming soon.\n"; }


