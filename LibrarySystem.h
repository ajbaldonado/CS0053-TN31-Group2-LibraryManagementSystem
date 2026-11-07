#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include "Book.h"

extern std::vector<Book> libraryCatalog;

//aj
void addBook();
void removeBook();
void updateBook();
void viewAllBooks();

void searchBook();
void generateSummary();

void borrowBook();
void returnBook();

void loadFromFile();
void saveToFile();

#endif