#include "Book.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// func prototypes
void printLibrary(vector<Book> &);
void printBook(Book *, bool);
void addBook(vector<Book> &);
void checkoutBook(vector<Book> &);
void returnBook(vector<Book> &);
void addPublisher(Book *);
Book *searchByIsbn(int, vector<Book> &);

// ###########################################
// ############ Print Books ##################
// ###########################################
void printLibrary(vector<Book> &library)
{
	cout << "\nHere are all of the library's books: \n";
	// loop thru library
	for (int i = 0; i < library.size(); i++)
	{
		// pointer to current book
		Book *currentBook = &library[i];
		// print current book
		// briefPrint true
		printBook(currentBook, true);
	}
}

// print out the information of a book
// boolean used to print out all of the books
// avoid overloading user with information
void printBook(Book *book, bool briefPrint)
{
	cout << book->title << " By: " << book->author << '\n'
	     << "\tISBN: " << book->isbn << "\n";

	// retrun early if briefPrint is true
	if (briefPrint)
	{
		return;
	}

	// more detailed info availible if briefPrint is false
	cout << "\tPublished: " << book->year << '\n' << "\tGenre: ";

	switch (book->genre)
	{
	case Genre::Fiction:
		cout << "Fiction\n";
		break;
	case Genre::NonFiction:
		cout << "Non-Fiction\n";
		break;
	case Genre::History:
		cout << "History\n";
		break;
	case Genre::Memoir:
		cout << "Memoir\n";
		break;
	default:
		cout << "Unknown / Misc.\n";
	}

	if (book->containsPublisher)
	{
		cout << "\tPublised By: " << book->publisherInfo.publisherName
		     << " In: " << book->publisherInfo.location << '\n';
	}

	cout << "\tStatus: ";

	switch (book->status)
	{
	case Status::CheckedOut:
		cout << "Checked Out\n";
		break;
	case Status::Available:
		cout << "Available\n";
		break;
	}
}

// ###########################################
// ########### Add Book ######################
// ###########################################

// take library (book vector) by reference to ensure Book is added
void addBook(vector<Book> &library)
{
	cin.clear();
	cin.ignore(1000, '\n');

	// create new book
	Book newBook;

	// collect title (string)
	cout << "\nEnter Book Title: ";
	getline(cin, newBook.title);

	// collect author (string)
	cout << "\nEnter Book Author: ";
	getline(cin, newBook.author);

	unsigned short year;
	cout << "\nEnter Book year: ";
	// validate input
	while (true)
	{
		cin >> year;

		if (!cin.fail())
		{
			newBook.year = year;
			break;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid date entered\n Enter a valid year: ";
	}

	int genre;
	// validate input
	while (true)
	{
		cout << "\t1.Fiction\n"
		     << "\t2.Non-Fiction\n"
		     << "\t3.Memoir\n"
		     << "\t4.History\n";
		cout << "Choose a genre (1 - 4) ";

		cin >> genre;
		bool validInput = (genre >= 1) && (genre <= 4);

		if (!cin.fail() && validInput)
		{
			// type cast input to Genre enum type
			newBook.genre = static_cast<Genre>(genre);
			break;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid selection entered\n";
	}

	addPublisher(&newBook);

	// calculare an ISBN using the genre and number of books in library
	// kinda like dewey decimal!
	newBook.isbn =
	    (100 * static_cast<unsigned int>(newBook.genre)) + library.size();
	library.push_back(newBook);
	cout << "Book succesfully added. ISBN: " << newBook.isbn;
}
//
// ###########################################
// ########### Add Publisher #################
// ###########################################
void addPublisher(Book *book)
{
	char ans;

	cout << "Would you like to add Publisher Info? (y / n): ";
	cin >> ans;

	switch (ans)
	{
	case 'Y':
	case 'y':
	{
		break;
	}
	// user does not want to add a Publisher
	case 'N':
	case 'n':
	{
		return;
	}
		// invalid input
	default:
	{
		cout << "Invalid Option.\n";
		// recursive call
		addPublisher(book);
		// ensure function does not run again
		return;
	}
	}

	cin.clear();
	cin.ignore(10000, '\n');

	Publisher bookPublisher;

	cout << "Enter Publisher Name: ";
	getline(cin, bookPublisher.publisherName);

	cout << "Enter Publisher Location: ";
	getline(cin, bookPublisher.location);

	book->publisherInfo = bookPublisher;
	book->containsPublisher = true;
	cout << "Book Publisher Info succesfully added.\n";
}

// ###########################################
// ############ Search Books #################
// ###########################################

// simple linear search
// checks each book's ISBN
// returns pointer to book if book is found
// returns nullptr if book is not found
Book *searchByIsbn(vector<Book> &library)
{
	cout << "Please enter an ISBN to search for: ";
	int isbn;
	cin >> isbn;
	if (cin.fail())
	{
		cout << "Invalid input provided.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		return searchByIsbn(library);
	}

	// pointer used to store current book
	Book *currentBook;

	// loop thru books
	for (int i = 0; i < library.size(); i++)
	{
		// assign current book to book at itteratio
		currentBook = &(library[i]);

		// if ISBNs match, return
		if (currentBook->isbn == isbn)
		{
			// case where book is found
			return currentBook;
		}
	}

	// return nullptr if book cannot be found
	return nullptr;
}

// ###########################################
// ########## Update Status of Book ##########
// ###########################################
void checkoutBook(vector<Book> &library)
{
	Book *book = nullptr;

	book = searchByIsbn(library);

	// user attempts to check out a book that does not exist
	if (book == nullptr)
	{
		cout << "Book could not be found.\n";
		return;
	}

	if (book->status == Status::CheckedOut)
	{
		cout << "Book is currently checked out and unavailable\n";
		return;
	}

	book->status = Status::CheckedOut;
	cout << "You have succesfully checked out " << book->title << ".\n";
}

void returnBook(vector<Book> &library)
{
	Book *book = nullptr;

	book = searchByIsbn(library);

	// user attempts to check out a book that does not exist
	if (book == nullptr)
	{
		cout << "Book could not be found.\n";
		return;
	}

	if (book->status == Status::Available)
	{
		cout << "Book has already been returned\n";
		return;
	}

	book->status = Status::Available;
	cout << "You have succesfully returned " << book->title << ".\n";
}

/*
 * ##########################################
 * ############ MAIN FUNCTION ###############
 * ##########################################
 */

int main()
{
	vector<Book> library;
	int choice;
	// flag for looping menue
	bool cont = true;
	// menu loop
	// ends when cont flag is false
	while (cont)
	{
		cout << "\n\t\t##### library program #####\n\n";

		cout << "\t1.Add a new Book\n"
		     << "\t2.Search for a book (ISBN)\n"
		     << "\t3.Checkout a book\n"
		     << "\t4.Return a book\n"
		     << "\t5.Print all books\n"
		     << "\t6.Quit\n";

		cout << "Select an option: ";
		cin >> choice;

		if (cin.fail())
		{
			choice = -1;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}

		cout << '\n';

		switch (choice)
		{
			// add book case
		case 1:
		{
			addBook(library);
			break;
		}
			// search for a book
		case 2:
		{
			Book *searchedBook = nullptr;
			searchedBook = searchByIsbn(library);

			if (searchedBook == nullptr)
			{
				cout << "Book could not be found\n";
			}
			else
			{
				cout << "Book located!\n";
				// print full info on book
				printBook(searchedBook, false);
			}

			break;
		}

			// Checkout a book
		case 3:
		{
			checkoutBook(library);

			break;
		}
			// Return a book
		case 4:
		{
			returnBook(library);
			break;
		}
			// print all books
		case 5:
		{
			printLibrary(library);
			break;
		}
			// Quit the program
		case 6:
		{
			cout << "Quitting program..." << endl;
			// continue flag set to false
			cont = false;
			break;
		}
		default:
		{
			cout << "Invalid option selected. Try again (1-5)\n";
			continue;
		}
		}
	}
	return 0;
}
