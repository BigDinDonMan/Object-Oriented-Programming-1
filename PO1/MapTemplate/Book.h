#ifndef _BOOK_H_
#define _BOOK_H_
#include <string>
#include <iostream>
using namespace std;

struct Author {
	string name;
	string surname;

	Author(string _name, string _surname);
	Author();
	void display() const;
};

class Book {
	public:
		Author author_info;
		string title;
		string category;
		bool is_available;
		unsigned number_of_pages;

		Book(string title);
		Book(Author info, string _title, string _category, bool available, unsigned pages_num);
		~Book();

		void display() const;

		friend std::ostream& operator << (std::ostream& stream, const Book& obj);
};

#endif