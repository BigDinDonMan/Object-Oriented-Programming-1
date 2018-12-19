#include "Employee.h"
#include <iostream>

Employee::Employee() {
	Name = Position = "";
	Age = 0;
}

Employee::Employee(std::string name, std::string position, unsigned age) {
	this->Name = name;
	this->Position = position;
	this->Age = age;
}

Employee::~Employee() {
	this->Name.clear();
	this->Position.clear();
	this->Age = 0;
}

std::ostream& operator << (std::ostream& stream, const Employee& object) {
	stream << object.Name << ", " << object.Position << ", age " << object.Age;
	return stream;
}