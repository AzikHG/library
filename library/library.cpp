#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Book {
private:
    string title;
    string author;
    double price;
    int quantity;

public:
    Book(const string& t, const string& a, double p, int q)
        : title(t), author(a), price(p), quantity(q) {
    }

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Decrease quantity when book is purchased
    bool purchase(int amount) {
        if (amount <= quantity) {
            quantity -= amount;
            return true;
        }
        return false;
    }

    // Display book information
    void display() const {
        cout << "\nTitle: " << title
            << "\nAuthor: " << author
            << "\nPrice: " << price << " tg"
            << "\nQuantity Available: " << quantity << endl;
    }

    // Save book data to file
    void saveToFile(ofstream& file) const {
        file << title << "\n" << author << "\n" << price << "\n" << quantity << "\n";
    }
};

class Library {
private:
    vector<Book> books;
    const string filename = "library_data.txt";

public:
    // Load books when library is created
    Library() {
        loadBooks();
    }

    // Save books when library is destroyed
    ~Library() {
        saveBooks();
    }

    // Add a new book to the library
    void addBook() {
        string title, author;
        double price;
        int quantity;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter book title: ";
        getline(cin, title);

        cout << "Enter author name: ";
        getline(cin, author);

        cout << "Enter price (tg): ";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        books.emplace_back(title, author, price, quantity);
        cout << "\nBook added successfully!" << endl;
    }

    // Display all books
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "\nNo books in library." << endl;
            return;
        }

        cout << "\n=== Library Catalog ===" << endl;
        for (const auto& book : books) {
            book.display();
            cout << "-------------------" << endl;
        }
    }

    // Search for books by title
    void searchBook() const {
        if (books.empty()) {
            cout << "\nNo books in library." << endl;
            return;
        }

        string searchTitle;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter book title to search: ";
        getline(cin, searchTitle);

        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle() == searchTitle) {
                cout << "\nBook found!" << endl;
                book.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nBook not found." << endl;
        }
    }

    // Purchase a book
    void purchaseBook() {
        if (books.empty()) {
            cout << "\nNo books available for purchase." << endl;
            return;
        }

        string title;
        int quantity;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter book title to purchase: ";
        getline(cin, title);

        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.display();

                cout << "Enter quantity to purchase: ";
                cin >> quantity;

                if (book.purchase(quantity)) {
                    double totalCost = book.getPrice() * quantity;
                    cout << "\nPurchase successful!"
                        << "\nTotal cost: " << totalCost << " tg" << endl;
                }
                else {
                    cout << "\nInsufficient quantity available." << endl;
                }
                return;
            }
        }

        cout << "\nBook not found." << endl;
    }

private:
    // Save books to file
    void saveBooks() const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                book.saveToFile(file);
            }
            file.close();
        }
    }

    // Load books from file
    void loadBooks() {
        ifstream file(filename);
        if (file.is_open()) {
            string title, author;
            double price;
            int quantity;

            while (getline(file, title)) {
                getline(file, author);
                file >> price;
                file >> quantity;
                file.ignore(numeric_limits<streamsize>::max(), '\n');

                books.emplace_back(title, author, price, quantity);
            }
            file.close();
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\n=== Electronic Library System ===" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Purchase Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";

        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.displayAllBooks();
            break;
        case 3:
            library.searchBook();
            break;
        case 4:
            library.purchaseBook();
            break;
        case 5:
            cout << "\nThank you for using the Electronic Library System!" << endl;
            return 0;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}