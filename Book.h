#pragma once
#include <string>

// Enum to track if book can be taken out
enum status
{
	Available,
	CheckedOut
};

// Boook struct
struct Book
{
	std::string title;
	std::string author;
	int isbn;
	short year;
};
