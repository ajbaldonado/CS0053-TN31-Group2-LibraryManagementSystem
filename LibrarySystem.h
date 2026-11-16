#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include "Book.h"
#include "User.h"

extern std::vector<Book> libraryCatalog;
extern std::vector<User> userList;
extern User* currentUser;

// aj
void addBook();
void removeBook();
void updateBook();
void viewAllBooks();

// justine
void searchBook();
void generateSummary();

// maxine
void borrowBook();
void returnBook();

// aaron
void loadFromFile();
void saveToFile();
void loadUsersFromFile();
void saveUsersToFile();
bool loginUser();
void registerUser();

#endif