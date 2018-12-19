#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include <string>

class Employee {
	private:
		std::string Name;

	public:
		std::string Position;
		unsigned Age;

		Employee();
		Employee(std::string name, std::string position, unsigned age);
		~Employee();

		friend std::ostream& operator << (std::ostream& stream, const Employee& object);
};

#endif