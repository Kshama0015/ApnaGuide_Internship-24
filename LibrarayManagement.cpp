#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using std::cerr;
using std::cin;
using std::cout;
using std::find_if;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;

class Book
{
public:
    Book(const string &title, const string &author)
        : title_(title), author_(author), available_(true) {}

    const string &getTitle() const { return title_; }
    const string &getAuthor() const { return author_; }
    bool isAvailable() const { return available_; }
    void setAvailable(bool available) { available_ = available; }

private:
    string title_;
    string author_;
    bool available_;
};

class LibraryPatron
{
public:
    explicit LibraryPatron(const string &name) : name_(name) {}

    const string &getName() const { return name_; }

    bool borrowBook(shared_ptr<Book> book)
    {
        if (book->isAvailable())
        {
            borrowedBooks_.push_back(book);
            book->setAvailable(false);
            return true;
        }
        return false;
    }

    void returnBook(shared_ptr<Book> book)
    {
        auto it = std::find(borrowedBooks_.begin(), borrowedBooks_.end(), book);
        if (it != borrowedBooks_.end())
        {
            borrowedBooks_.erase(it);
            book->setAvailable(true);
        }
        else
        {
            cerr << "Error: Book not found in borrowed books.\n";
        }
    }

    const vector<shared_ptr<Book>> &getBorrowedBooks() const
    {
        return borrowedBooks_;
    }

private:
    string name_;
    vector<shared_ptr<Book>> borrowedBooks_;
};

class Library
{
public:
    void addBook(const string &title, const string &author)
    {
        books_.emplace_back(make_shared<Book>(title, author));
    }

    void displayAvailableBooks() const
    {
        cout << "Available Books:\n";
        for (size_t i = 0; i < books_.size(); ++i)
        {
            if (books_[i]->isAvailable())
            {
                cout << i + 1 << ". Title: " << books_[i]->getTitle() << ", Author: " << books_[i]->getAuthor() << '\n';
            }
        }
    }

    bool checkoutBook(size_t index, shared_ptr<LibraryPatron> patron)
    {
        if (index < books_.size() && books_[index]->isAvailable() && patron->borrowBook(books_[index]))
        {
            return true;
        }
        cerr << "Error: Book is not available or index is invalid.\n";
        return false;
    }

    void returnBook(const string &title, shared_ptr<LibraryPatron> patron)
    {
        auto book = findBookByTitle(title);
        if (book)
        {
            patron->returnBook(book);
        }
        else
        {
            cerr << "Error: Book \"" << title << "\" not found in library.\n";
        }
    }

    void addPatron(const string &name)
    {
        patrons_.emplace_back(make_shared<LibraryPatron>(name));
    }

    void displayPatrons() const
    {
        cout << "Library Patrons:\n";
        for (const auto &patron : patrons_)
        {
            cout << "Name: " << patron->getName() << ", Borrowed Books: ";
            for (const auto &book : patron->getBorrowedBooks())
            {
                cout << book->getTitle() << ", ";
            }
            cout << '\n';
        }
    }

    shared_ptr<LibraryPatron> findPatronByName(const string &name) const
    {
        auto it = find_if(patrons_.begin(), patrons_.end(), [&](const shared_ptr<LibraryPatron> &patron)
                          { return patron->getName() == name; });
        if (it != patrons_.end())
        {
            return *it;
        }
        cerr << "Error: Patron \"" << name << "\" not found.\n";
        return nullptr;
    }

private:
    shared_ptr<Book> findBookByTitle(const string &title) const
    {
        auto it = find_if(books_.begin(), books_.end(), [&](const shared_ptr<Book> &book)
                          { return book->getTitle() == title; });
        return it != books_.end() ? *it : nullptr;
    }

    vector<shared_ptr<Book>> books_;
    vector<shared_ptr<LibraryPatron>> patrons_;
};

void displayMenu()
{
    cout << "\nLibrary Menu:\n";
    cout << "1. Display available books\n";
    cout << "2. Borrow a book\n";
    cout << "3. Return a book\n";
    cout << "4. Display patrons\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Library library;
    library.addBook("To Kill a Mockingbird", "Harper Lee");
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook("1984", "George Orwell");

    library.addPatron("Raj Shukla");
    library.addPatron("Rahul Sharma");

    string patronName;
    cout << "Enter your name: ";
    getline(cin, patronName);

    auto patron = library.findPatronByName(patronName);
    if (!patron)
    {
        cerr << "Exiting program due to patron not found.\n";
        return 1;
    }

    int choice;
    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice)
        {
        case 1:
            library.displayAvailableBooks();
            break;
        case 2:
        {
            library.displayAvailableBooks();
            size_t bookIndex;
            cout << "Enter the number of the book you want to borrow: ";
            cin >> bookIndex;
            --bookIndex; // Adjust for zero-based index
            if (!library.checkoutBook(bookIndex, patron))
            {
                cout << "Error: Unable to borrow book.\n";
            }
            break;
        }
        case 3:
        {
            string title;
            cout << "Enter the title of the book you want to return: ";
            getline(cin, title);
            library.returnBook(title, patron);
            break;
        }
        case 4:
            library.displayPatrons();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
