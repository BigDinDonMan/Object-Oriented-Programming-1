#ifndef STACK
#define STACK

#define DEFAULT_STACK_SIZE 10

class Stack {
	private:
		int current_size;
		int *stack;
		int capacity;
	public:
		Stack();
		Stack(unsigned size);
		~Stack();

		int get_capacity() const;
		int get_current_size() const;
		bool is_empty() const;
		bool is_full() const;
 
		void display() const;
		void clear();

		int push_back(int value);
		int pop();
};


#endif