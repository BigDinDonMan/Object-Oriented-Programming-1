#include "Book.h"

Book::Book(Author info, string _title, string _category, bool available, unsigned pages_num) {
	this->author_info = info;
	this->title = _title;
	this->category = _category;
	this->is_available = available;
	this->number_of_pages = pages_num;
}

Book::~Book() {
	this->author_info.name.clear();
	this->author_info.surname.clear();
	this->title.clear();
	this->category.clear();
	this->number_of_pages = 0;
}

Book::Book(string title) {
	this->title = title;
}

void Book::display() const {
	cout << "\"" << this->title << "\"" << endl;
	cout << "author: ";
	this->author_info.display();
	cout << endl;
	cout << "category: " << this->category << endl;
	cout << "available: " << (!this->is_available ? "no" : "yes") << endl;
	cout << "number of pages: " << this->number_of_pages << endl;
}

std::ostream& operator << (std::ostream& stream, const Book& obj) {
	obj.display();
	return stream;
}

Author::Author(string _name, string _surname) : name(_name), surname(_surname) {}
void Author::display() const {
	cout << name << " " << surname;
}
Author::Author() : name(""), surname("") {}