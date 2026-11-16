#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "LibrarySystem.h"

using namespace std;

vector<Book> libraryCatalog;
vector<User> userList;
User* currentUser = nullptr;

// aaron - FILE HANDLING

void loadFromFile() {
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

void saveToFile() {
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

void loadUsersFromFile() {
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

void saveUsersToFile() {
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

// aaron - AUTHENTICATION

bool loginUser() {
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

void registerUser() {
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


void addBook() {
    cout << "(For testing/debugging purposes only) add new book!\n";
}
void removeBook() {
    cout << "(For testing/debugging purposes only) remove book!\n";
}
void updateBook() {
    cout << "(For testing/debugging purposes only) update book!\n";
}
void viewAllBooks() {}

void searchBook() {}
void generateSummary() {}
void borrowBook() {}
void returnBook() {}