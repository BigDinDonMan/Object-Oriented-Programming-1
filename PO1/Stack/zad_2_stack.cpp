#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include "stack.h"

using namespace std;

int main(void) {

	Stack *new_stack = new Stack();
	for (int i = 0; i < 25; ++i) {
		new_stack->push_back(i);
	}
	cout << "capacity of the stack: " << new_stack->get_capacity() << endl;
	new_stack->display();
	for (int i = 0; i < 10; ++i) {
		cout << "pop value: " << new_stack->pop() << endl;
	}
	cout << "current stack size: " << new_stack->get_current_size() << endl;
	new_stack->display();
	delete new_stack;
	return 0;
}