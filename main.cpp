#include "Book.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void addBook(vector<Book> &);

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
	// calculare an ISBN using the genre and number of books in library
	// kinda like dewey decimal!
	newBook.isbn =
	    (100 * static_cast<unsigned int>(newBook.genre)) + library.size();
	library.push_back(newBook);
}

Book *searchByIsbn(int isbn)
{
}

int main()
{
	vector<Book> library;
	int choice;
	bool cont = true;
	// menu loop
	while (cont)
	{
		cout << "\t\t##### library program #####\n\n";

		cout << "\t1.Add a new Book\n"
		     << "\t2.Search for a book (ISBN)\n"
		     << "\t3.Checkout a book\n"
		     << "\t4.Returm a nook\n"
		     << "\t5.Quit\n";

		cout << "Select an option: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please enter a number.\n";
			continue;
		}

		switch (choice)
		{
		case 1:
			addBook(library);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			cout << "Quitting program..." << endl;
			cont = false;
			break;
		default:
			cout << "Invalid option selected. Try again (1-5)\n";
			continue;
		}
	}
	return 0;
}
