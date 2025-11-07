#pragma once
#include <string>

// Enum to track if book can be taken out
enum class Status
{
	Available,
	CheckedOut
};
// Enum for book Genre
enum Genre
{
	Fiction,
	NonFiction,
	Memoir,
	Cooking,
	History,
	Childrens
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
};
