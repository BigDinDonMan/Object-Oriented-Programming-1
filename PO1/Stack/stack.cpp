#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include "stack.h"

using namespace std;

Stack::Stack() {
	this->stack = new int[DEFAULT_STACK_SIZE];
	this->capacity = DEFAULT_STACK_SIZE;
	this->current_size = 0;
}
Stack::Stack(unsigned size) {
	this->stack = new int[size];
	this->capacity = size;
	this->current_size = 0;
}
Stack::~Stack() {
	this->current_size = this->capacity = 0;
	delete[] this->stack;
}

int Stack::get_capacity() const {
	return this->capacity;
}

int Stack::get_current_size() const {
	return this->current_size;
}

bool Stack::is_empty() const {
	return this->current_size == 0;
}

bool Stack::is_full() const {
	return this->current_size == this->capacity;
}

void Stack::display() const {
	if (!current_size) return;
	for (int i = 0; i < this->current_size; ++i) {
		cout << this->stack[i] << " ";
	}
	cout << endl;
}

void Stack::clear() {
	memset(this->stack, 0, this->current_size * sizeof(int));
	this->current_size = 0;
}

int Stack::push_back(int value) {
	if (this->is_full()) {
		int *tempPtr = (int*)realloc(this->stack, this->capacity * 2 * sizeof(int));
		if (!tempPtr) {
			return 1;
		}	
		this->stack = tempPtr;
		this->capacity *= 2;
	}
	this->stack[this->current_size++] = value;
	return 0;
}

int Stack::pop() {
	if (this->is_empty()) {
		fprintf(stderr, "Nothing to remove, stack is empty\n");
		return 1;
	}
	return this->stack[this->current_size-- - 1];
}