#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;

    Book() : id(0), title(""), author(""), isAvailable(true) {}
    Book(int bId, string bTitle, string bAuthor)
        : id(bId), title(bTitle), author(bAuthor), isAvailable(true) {}
};

#endif