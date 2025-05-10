#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class
class Book {
protected:
    int id;
    string title;
    string author;
    bool isIssued;

public:
    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), isIssued(false) {
    }

    virtual void display() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author;
        cout << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }

    int getId() const { return id; }
    string getTitle() const { return title; }

    void issue() { isIssued = true; }
    void returnBook() { isIssued = false; }
};

// Derived class
class Library {
private:
    vector<Book*> books;

public:
    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }

    void addBook(int id, const string& title, const string& author) {
        books.push_back(new Book(id, title, author));
        cout << "Book added successfully.\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }

        cout << "\nLibrary Collection:\n";
        for (const auto& book : books) {
            book->display();
        }
    }

    void searchBook(int id) const {
        for (const auto& book : books) {
            if (book->getId() == id) {
                cout << "Book found:\n";
                book->display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void removeBook(int id) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getId() == id) {
                delete* it;
                books.erase(it);
                cout << "Book removed successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

// Main program
int main() {
    Library lib;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\n=== Library Menu ===\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n4. Remove Book\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            lib.addBook(id, title, author);
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3:
            cout << "Enter Book ID to search: ";
            cin >> id;
            lib.searchBook(id);
            break;
        case 4:
            cout << "Enter Book ID to remove: ";
            cin >> id;
            lib.removeBook(id);
            break;
        case 5:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
