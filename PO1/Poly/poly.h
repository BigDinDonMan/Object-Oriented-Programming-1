#ifndef _POLY_H_
#define _POLY_H_
#include <iostream>
#include <cmath>
#include <map>
#include <cstdio>
using namespace std;

class Poly {
	private:
		map<int, float, greater<int>> data;
	public:
		Poly();
		Poly(const Poly& other);
		Poly(float val);
		~Poly();

		Poly& operator=(float val);
		float& operator[](int index);
		float operator()(float value);

		void display() const;

		friend Poly operator+(const Poly&, const Poly&);
		friend Poly operator*(const Poly&, const Poly&);
		friend std::ostream& operator << (std::ostream& stream, const Poly& poly);

};

#endif