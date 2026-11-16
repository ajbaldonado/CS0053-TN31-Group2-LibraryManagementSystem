#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
    string borrowedBy; // Username of borrower, or "NONE"
    string dueDate;    // YYYY-MM-DD, or "NONE"

    Book() : id(0), title(""), author(""), isAvailable(true), borrowedBy("NONE"), dueDate("NONE") {}
    Book(int bId, string bTitle, string bAuthor)
        : id(bId), title(bTitle), author(bAuthor), isAvailable(true), borrowedBy("NONE"), dueDate("NONE") {}
    Book(int bId, string bTitle, string bAuthor, bool bAvail, string bBorrower, string bDue)
        : id(bId), title(bTitle), author(bAuthor), isAvailable(bAvail), borrowedBy(bBorrower), dueDate(bDue) {}
};

#endif