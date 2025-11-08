#pragma once
#include "Publisher.h"
#include <string>

// Enum to track if book can be taken out
enum class Status
{
	Available,
	CheckedOut
};
// Enum for book Genre
enum class Genre
{
	Fiction,
	NonFiction,
	Memoir,
	History
};

// Boook struct
struct Book
{
	std::string title;
	std::string author;
	short year;
	// Books will be available by default
	Status status = Status::Available;
	int isbn;
	Genre genre;
	// nested struct
	Publisher publisherInfo;
	bool containsPublisher = false;
};
