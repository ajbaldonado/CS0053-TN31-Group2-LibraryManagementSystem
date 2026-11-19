#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "Book.h"
#include "User.h"
#include <vector>

extern std::vector<Book> libraryCatalog;
extern std::vector<User> userList;
extern User *currentUser;

void addBook();
void removeBook();
void updateBook();
void viewAllBooks();

void searchBook();
void generateSummary();

void borrowBook();
void returnBook();
void viewMyBooks();
void viewOverdueBooks();

void loadFromFile();
void saveToFile();
void loadUsersFromFile();
void saveUsersToFile();
bool loginUser();
void registerUser();

#endif
