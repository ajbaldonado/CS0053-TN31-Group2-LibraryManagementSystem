Library Management System
Created by: GitLog

Members: 
Baldonado, Arthur John F.
Grutas, Aaron Nathaniel L.
Sangil, Justine Fernando C.
Sinang, Sophia Maxine Jae S.

PROJECT PURPOSE: A simple library management system that allows for users to manage and log books within the system. It allows the user to have an organized feel when managing their books, as if it were in a library. The system focuses on logging and storing books based on a given user's credentials. Different users may utilize the system through our file handling, which can save and store different accounts that were entered locally in the device.

Features:
- Basic Features: The system contains basic features that focus on interacting with the system catalog. This includes the ability to add books into the catalog, specifying the book title and the author to be put into the catalog, the system will automatically assign a book ID for other designated uses. Additional features include the removal and updating of other user-registered books by utilizing the book ID to either remove or update the information of the book.

- File Handling: The system utilizes different file handling techniques to allow for local data storage and the use of account saving. The system allows for logging in and out of user accounts to save different saved logs and entries made from a specific account. Each account holds different books borrowed, books entered and books returned. This feature also allows for a user and an admin account to be used separately, having completely different access points for both the user and the admin.

- Borrowing System and Book Tracker: The library system contains a built-in borrowing system, wherein the user can log specific books they wish to borrow that are within the catalog. This feature also utilizes the file handling features of the code alongside time-related functions to take note of when are the dates where certain books were borrowed. The max amount of books that a single user can borrow is 3. The borrowing system also takes note of when a book is borrowed beyond the return date, in which the system will file a fine towards the account of the user that is overdue.

- Generalization and Summarization of Data: The system contains a summarization function wherein different statistics on borrowed and returned books are shown. It also contains a function that returns currently logged books within the catalog, allowing the user to have a look on what books are available to borrow and currently being borrowed by other users.

Compiler Used: Visual Studio Code

Compilation Process: Go to the main.cpp file and press Ctrl + Shift + B to compile the code, then run it through the terminal by typing ./library.exe.

Sample Input / Output:

Adding of a Book (admin)
=====================================
      LIBRARY MANAGEMENT SYSTEM      
=====================================
1. Add New Book
2. View All Books
3. Search Catalog
4. Update Book Details
5. Remove Book
6. Borrow Book
7. Return Book
8. Generate Summary Report
9. View Overdue Books
10. Logout
=====================================
Enter choice (1-10): 1
Enter book title: Dragon Ball
Enter book author: Akira Toriyama
Book added successfully with ID: 11

View All Books (user)
=====================================
      LIBRARY MANAGEMENT SYSTEM      
=====================================
Logged in as: AJ
1. View All Books
2. Search Catalog
3. Borrow Book
4. Return Book
5. My Borrowed Books
6. Logout
7. Exit
=====================================
Enter choice (1-7): 1
ID    Title                         Author                   Status      Due Date
-------------------------------------------------------------------------------------
1     To Kill a Mockingbird         Harper Lee               Available   -
2     1984                          George Orwell            Available   -
3     Pride and Prejudice           Jane Austen              Available   -
4     The Great Gatsby              F. Scott Fitzgerald      Available   -
5     Noli Me Tangere               Jose Rizal               Available   -
6     El Filibusterismo             Jose Rizal               Available   -
7     The Hobbit                    J.R.R. Tolkien           Available   -
8     A Gentle Reminder             Bianca Sparacino         Available   -
9     The Alchemist                 Paulo Coelho             Available   -
10    Introduction to Algorithms    Thomas H. Cormen         Available   -
11    Dragon Ball                   Akira Toriyama           Available   -

Search Catalog (user)
=====================================
      LIBRARY MANAGEMENT SYSTEM      
=====================================
Logged in as: AJ
1. View All Books
2. Search Catalog
3. Borrow Book
4. Return Book
5. My Borrowed Books
6. Logout
7. Exit
=====================================
Enter choice (1-7): 2
Enter ID, title, or author: Dragon Ball

SEARCH RESULTS
ID:       11
Title:    Dragon Ball
Author:   Akira Toriyama
Status:   Available

Borrowing Books (user)
=====================================
      LIBRARY MANAGEMENT SYSTEM      
=====================================
Logged in as: AJ
1. View All Books
2. Search Catalog
3. Borrow Book
4. Return Book
5. My Borrowed Books
6. Logout
7. Exit
=====================================
Enter choice (1-7): 3
ID    Title                         Author                   Status      Due Date
-------------------------------------------------------------------------------------
1     To Kill a Mockingbird         Harper Lee               Available   -
2     1984                          George Orwell            Available   -
3     Pride and Prejudice           Jane Austen              Available   -
4     The Great Gatsby              F. Scott Fitzgerald      Available   -
5     Noli Me Tangere               Jose Rizal               Available   -
6     El Filibusterismo             Jose Rizal               Available   -
7     The Hobbit                    J.R.R. Tolkien           Available   -
8     A Gentle Reminder             Bianca Sparacino         Available   -
9     The Alchemist                 Paulo Coelho             Available   -
10    Introduction to Algorithms    Thomas H. Cormen         Available   -
11    Dragon Ball                   Akira Toriyama           Available   -

Enter book ID to borrow: 11
You borrowed "Dragon Ball".
Due date: 2026-11-26 (7 days from today).