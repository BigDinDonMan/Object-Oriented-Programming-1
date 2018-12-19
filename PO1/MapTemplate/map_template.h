#ifndef _MAP_TEMPLATE_H_
#define _MAP_TEMPLATE_H_

#include <iostream>
#include <cstring>
#include <string>
#include <exception>
using namespace std;

class KeyAlreadyExistsException : std::exception {
	public:
		virtual const char* what() const throw() {
			return "Key already exists!\n";
		}

};

template<typename Key, typename Value>
class map_template {
	struct data_node {
		Key key;
		Value value;
		data_node *next;

		data_node() {
			next = NULL;
		}
		data_node(Key k, Value val) : key(k), value(val), next(NULL) {}
	};

	private:
		data_node *begin;
		data_node *end;

	public:
		map_template() {
			begin = end = NULL;
		}

		map_template(const map_template<Key, Value>& other) {
			this->begin = this->end = NULL;
			data_node *temp = other.begin;
			while (temp) {
				try {
					this->Add(temp->key, temp->value);
				} catch (const KeyAlreadyExistsException&) {}
				temp = temp->next;
			}
		}

		~map_template() {
			if (!this->is_empty()) {
				data_node *temp = this->begin;
				while (temp) {
					data_node *temp_ptr = temp->next;
					delete temp;
					temp = temp_ptr;
				}
			}
		}
		
		map_template<Key, Value>& operator=(const map_template<Key, Value>& other) { //TODO: ogarnąć tak żeby móc zaktualizować obiekt przez przypisanie
			data_node *temp = other.begin;
			while (temp) {
				try {
					this->Add(temp->key, temp->value);
				} catch (const KeyAlreadyExistsException& ex) {
					Value *tempVal = this->Find(temp->key);
					*tempVal = temp->value;
				}
				temp = temp->next;
			}
			return *this;
		}

		bool is_empty() const {
			if (!begin && !end) return true;
			return false;
		}

		void Add(Key key, Value value) {
			if (this->Find(key)) {
				throw KeyAlreadyExistsException();
			}
			data_node *newNode = new data_node(key, value);
			if (this->is_empty()) {
				begin = end = newNode;
			} else {
				end->next = newNode;
				end = newNode;
			}
		}

		Value* Find(Key k) const {
			if (this->is_empty()) return NULL;
			data_node *temp = this->begin;
			if (!temp) return NULL;
			while (temp) {
				if (temp->key == k) return &temp->value;
				temp = temp->next;
			}
			return NULL;
		}

		unsigned get_size() const {
			if (this->is_empty()) return 0;
			data_node *temp = this->begin;
			unsigned counter = 0;
			while (temp) {
				++counter;
				temp = temp->next;
			}
			return counter;
		}

		void display() const {
			data_node *temp = this->begin;
			while (temp) {
				cout << temp->key << " : " << temp->value << endl;
				temp = temp->next;
			}
		}

		friend std::ostream& operator << (std::ostream& stream, const map_template<Key, Value>& object) {
			object.display();
			return stream;
		}
			
};	



#endif