#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include "complex.h"

using namespace std;

int main(void) {

	Complex *first = new Complex(2.3f, 4.5f), *second = new Complex(-1.0f, -2.5f), *result = new Complex();

	cout << "********************" << endl;
	*result = *first + *second;
	cout << "result of addition: " << *result << endl;
	cout << "Conj(): " << result->conj() << endl;
	cout << "Abs(): " << result->abs() << endl;
	cout << "Phase(): " << result->phase() << endl;

	cout << "********************" << endl;
	*result = *first - *second;
	cout << "result of subtraction: " << *result << endl;
	cout << "Conj(): " << result->conj() << endl;
	cout << "Abs(): " << result->abs() << endl;
	cout << "Phase(): " << result->phase() << endl;

	cout << "********************" << endl;
	*result = *first * (*second);
	cout << "result of multiplication: " << *result << endl;
	cout << "Conj(): " << result->conj() << endl;
	cout << "Abs(): " << result->abs() << endl;
	cout << "Phase(): " << result->phase() << endl;

	cout << "********************" << endl;
	*result = *first / *second;
	cout << "result of division: " << *result << endl;
	cout << "Conj(): " << result->conj() << endl;
	cout << "Abs(): " << result->abs() << endl;
	cout << "Phase(): " << result->phase() << endl;

	cout << "********************" << endl;
	*result = *first + 20.0f;
	cout << "result of adding a normal float: " << *result << endl;
	cout << "********************" << endl;
	*result = 20.0f;
	cout << "result of assignment: " << *result << endl;

	Complex *int_result = new Complex();
	*int_result = 2 - *result;
	cout << "result of int subtraction: " << *int_result << endl;
	cout << "result of -Complex: " << -*int_result << endl;

	delete first;
	delete second;
	delete result;
	delete int_result;
	return 0;
}
