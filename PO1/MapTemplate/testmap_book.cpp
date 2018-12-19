#include "map_template.h"
#include "Book.h"


int main(void) {

	map_template<string, Book> library;
	library.Add("Gra o Tron", Book(Author("George", "Martin"), "Gra o Tron", "Fantasy", true, 534));
	library.Add("Harry Potter i Kamień Filozoficzny", Book(Author("J.K.", "Rowling"), "Harry Potter i Kamień Filozoficzny", "Akcja", false, 666));
	cout << "********Original********" << endl;
	cout << library;
	map_template<string, Book> new_Library;
	new_Library = library;
	cout << "********copy********" << endl;
	cout << new_Library;
	Book *toFind = new_Library.Find("Gra o Tron");
	if (toFind) {
		toFind->is_available = !toFind->is_available;
		toFind->category = "Akcja";
		library = new_Library;
		cout << "********updated original********" << endl;
		cout << library;
	} else {
		cout << "couldnt find such title";
	}

	return 0;
}