#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include "LibrarySystem.h"d

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

static const int LOAN_DAYS = 7;           // how many days a book may be borrowed
static const int FINE_PER_DAY = 5;         // fine (PHP) for every day a book is overdue
static const int MAX_BORROWED_BOOKS = 3;  // most books one user can hold at a time

// Today's date as "YYYY-MM-DD"
static string getTodayDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return string(buf);
}

// Turns "YYYY-MM-DD" into a tm; returns false if the text is not a valid date
static bool parseDate(const string& s, tm& out) {
    int y, m, d;
    if (sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) != 3) return false;
    if (m < 1 || m > 12 || d < 1 || d > 31) return false;
    out = tm();
    out.tm_year = y - 1900;
    out.tm_mon = m - 1;
    out.tm_mday = d;
    out.tm_hour = 12; // noon, so daylight-saving shifts never change the day
    return true;
}

// Returns date + days as "YYYY-MM-DD"
static string addDays(const string& date, int days) {
    tm t;
    if (!parseDate(date, t)) return "NONE";
    t.tm_mday += days;
    mktime(&t); // normalizes overflow (e.g. Jan 35 -> Feb 4)
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t);
    return string(buf);
}

// Number of days from 'from' to 'to' (negative if 'to' is earlier)
static int daysBetween(const string& from, const string& to) {
    tm a, b;
    if (!parseDate(from, a) || !parseDate(to, b)) return 0;
    double secs = difftime(mktime(&b), mktime(&a));
    return (int)floor(secs / 86400.0 + 0.5);
}

// How many days past the due date a book is today (0 if not overdue)
static int daysOverdue(const string& dueDate) {
    if (dueDate == "NONE") return 0;
    int late = daysBetween(dueDate, getTodayDate());
    return late > 0 ? late : 0;
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


void loadFromFile() { // loads previous book records
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

void saveToFile() { // saves book records
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

void loadUsersFromFile() { // reads/loads user accounts; creates a default admin and user acc
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

void saveUsersToFile() { // saves registered accounts
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

bool loginUser() { // validates user credentials
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


void searchBook() { cout << "Search feature coming soon.\n"; }
void generateSummary() { cout << "Summary feature coming soon.\n"; }

// Lets the logged-in user borrow an available book and sets its due date
void borrowBook() {
    if (currentUser == nullptr) {
        cout << "You must be logged in to borrow a book.\n";
        return;
    }

    // Count what this user already has, and check for overdue books
    int borrowedCount = 0;
    bool hasOverdue = false;
    for (const auto& b : libraryCatalog) {
        if (!b.isAvailable && b.borrowedBy == currentUser->username) {
            borrowedCount++;
            if (daysOverdue(b.dueDate) > 0) hasOverdue = true;
        }
    }
    if (hasOverdue) {
        cout << "You have an overdue book. Please return it before borrowing another.\n";
        return;
    }
    if (borrowedCount >= MAX_BORROWED_BOOKS) {
        cout << "Borrow limit reached (" << MAX_BORROWED_BOOKS
             << " books). Please return a book first.\n";
        return;
    }

    if (libraryCatalog.empty()) {
        cout << "No books in the library.\n";
        return;
    }
    viewAllBooks();

    int id;
    cout << "\nEnter book ID to borrow: ";
    if (!readInt(id)) {
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    auto it = find_if(libraryCatalog.begin(), libraryCatalog.end(),
                      [id](const Book& b) { return b.id == id; });
    if (it == libraryCatalog.end()) {
        cout << "Book not found.\n";
        return;
    }
    if (!it->isAvailable) {
        if (it->borrowedBy == currentUser->username) {
            cout << "You already borrowed this book. It is due on " << it->dueDate << ".\n";
        } else {
            cout << "Sorry, this book is currently borrowed. Expected back on "
                 << it->dueDate << ".\n";
        }
        return;
    }

    it->isAvailable = false;
    it->borrowedBy = currentUser->username;
    it->dueDate = addDays(getTodayDate(), LOAN_DAYS);
    cout << "You borrowed \"" << it->title << "\".\n";
    cout << "Due date: " << it->dueDate << " (" << LOAN_DAYS << " days from today).\n";
}

// Returns a borrowed book. Users can only return their own books; admins can return any.
void returnBook() {
    if (currentUser == nullptr) {
        cout << "You must be logged in to return a book.\n";
        return;
    }
    bool isAdmin = (currentUser->role == "admin");

    if (isAdmin) {
        bool anyBorrowed = false;
        for (const auto& b : libraryCatalog) {
            if (!b.isAvailable) { anyBorrowed = true; break; }
        }
        if (!anyBorrowed) {
            cout << "No books are currently borrowed.\n";
            return;
        }
        viewAllBooks();
    } else {
        bool hasBooks = false;
        for (const auto& b : libraryCatalog) {
            if (!b.isAvailable && b.borrowedBy == currentUser->username) { hasBooks = true; break; }
        }
        if (!hasBooks) {
            cout << "You have no borrowed books to return.\n";
            return;
        }
        viewMyBooks();
    }

    int id;
    cout << "\nEnter book ID to return: ";
    if (!readInt(id)) {
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    auto it = find_if(libraryCatalog.begin(), libraryCatalog.end(),
                      [id](const Book& b) { return b.id == id; });
    if (it == libraryCatalog.end()) {
        cout << "Book not found.\n";
        return;
    }
    if (it->isAvailable) {
        cout << "This book is not currently borrowed.\n";
        return;
    }
    if (!isAdmin && it->borrowedBy != currentUser->username) {
        cout << "You can only return books that you borrowed.\n";
        return;
    }

    int late = daysOverdue(it->dueDate);
    cout << "\"" << it->title << "\" returned successfully.\n";
    if (late > 0) {
        cout << "This book was " << late << " day(s) overdue. Fine: PHP "
             << late * FINE_PER_DAY << ".\n";
    } else {
        cout << "Returned on time. Thank you!\n";
    }

    it->isAvailable = true;
    it->borrowedBy = "NONE";
    it->dueDate = "NONE";
}

// Shows the books the logged-in user currently has, with due dates
void viewMyBooks() {
    if (currentUser == nullptr) return;

    bool found = false;
    int totalFine = 0;
    for (const auto& b : libraryCatalog) {
        if (b.isAvailable || b.borrowedBy != currentUser->username) continue;

        if (!found) {
            cout << "\nYOUR BORROWED BOOKS\n";
            cout << left << setw(6) << "ID" << setw(30) << "Title"
                 << setw(14) << "Due Date" << "Status\n";
            cout << string(70, '-') << "\n";
            found = true;
        }

        int late = daysOverdue(b.dueDate);
        int left_ = daysBetween(getTodayDate(), b.dueDate); // days remaining
        cout << left << setw(6) << b.id << setw(30) << b.title << setw(14) << b.dueDate;
        if (late > 0) {
            cout << "OVERDUE by " << late << " day(s)\n";
            totalFine += late * FINE_PER_DAY;
        } else if (left_ == 0) {
            cout << "Due today\n";
        } else {
            cout << left_ << " day(s) left\n";
        }
    }

    if (!found) {
        cout << "You have no borrowed books.\n";
    } else if (totalFine > 0) {
        cout << "\nCurrent fines: PHP " << totalFine << "\n";
    }
}

// Admin report: every overdue book, who has it, and the fine so far
void viewOverdueBooks() {
    bool found = false;
    for (const auto& b : libraryCatalog) {
        int late = daysOverdue(b.dueDate);
        if (b.isAvailable || late <= 0) continue;

        if (!found) {
            cout << "\nOVERDUE BOOKS\n";
            cout << left << setw(6) << "ID" << setw(28) << "Title" << setw(16) << "Borrower"
                 << setw(13) << "Due Date" << setw(10) << "Days Late" << "Fine\n";
            cout << string(80, '-') << "\n";
            found = true;
        }
        cout << left << setw(6) << b.id << setw(28) << b.title << setw(16) << b.borrowedBy
             << setw(13) << b.dueDate << setw(10) << late
             << "PHP " << late * FINE_PER_DAY << "\n";
    }
    if (!found) {
        cout << "No overdue books.\n";
    }
}