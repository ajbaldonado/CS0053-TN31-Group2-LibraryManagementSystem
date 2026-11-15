#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
    string borrower; // Adding this, in case you guys want it to be specified

    Book() : id(0), title(""), author(""), isAvailable(true) {}
    Book(int bId, string bTitle, string bAuthor)
        : id(bId), title(bTitle), author(bAuthor), isAvailable(true) {}
};

#endif
