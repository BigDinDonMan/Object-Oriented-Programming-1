#include "poly.h"

using namespace std;

Poly::Poly() {
	this->data[0] = 0;
}
Poly::Poly(const Poly& other) {
	for (auto i = other.data.begin(); i != other.data.end(); ++i) {
		this->data[i->first] = i->second;
	}
}
Poly::Poly(float val) {
	this->data[0] = val;
}
Poly::~Poly() {
	this->data.clear();
}

Poly& Poly::operator=(float val) {
	this->data[0] = val;
	//cout << this->data[0] << " " << "here" << endl;
	return *this;
}

float& Poly::operator[](int index) {
	return this->data[index];
}

float Poly::operator()(float value) {
	float return_value = 0.f;
	for (auto i = this->data.begin(); i != this->data.end(); ++i) {
		return_value += i->second * pow(value, i->first);
	}
	return return_value;
}

void Poly::display() const {
	for (auto i = this->data.begin(); i != this->data.end(); ++i) {
		if (i == this->data.begin()) {
			if (i->second) printf("%.2f", i->second);
			if (i->first) {
				printf("x");
				if (i->first > 1) {
					printf("^%d", i->first);
				}
			} 
		} else {
			printf(i->second < 0.f ? " - " : " + ");
			if (i->second > 1) printf("%.2f", i->second < 0.f ? -(i->second) : i->second);
			if (i->first) {
				printf("x");
				if (i->first > 1) {
					printf("^");
					printf("%d", i->first);
				}
			} 
		}
	}
	cout << endl;
}

std::ostream& operator << (std::ostream& stream, const Poly& poly) {
	poly.display();
	return stream;
}

Poly operator+(const Poly& first, const Poly& second) {
	Poly new_poly(first);
	for (auto i = second.data.begin(); i != second.data.end(); ++i) {
		if (new_poly.data.find(i->first) != new_poly.data.end()) {
			new_poly[i->first] += i->second;
		} else {
			new_poly[i->first] = i->second;
		}
	}
	return new_poly;
}

Poly operator*(const Poly& first, const Poly& second) {
	Poly new_poly;
	for (auto i = first.data.begin(); i != first.data.end(); ++i) {
		for (auto j = second.data.begin(); j != second.data.end(); ++j) {
			float value = i->second * j->second;
			int key = i->first + j->first;
			if (new_poly.data.find(key) != new_poly.data.end()) {
				new_poly[key] += value;
			} else {
				new_poly[key] = value;
			}
		}
	}
	return new_poly;
}