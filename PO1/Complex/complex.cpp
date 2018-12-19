#include <cmath>
#include <iostream>
#include <cstring>
#include <string>
#include "complex.h"

using namespace std;

Complex::Complex(float re, float im) {
	this->re = re;
	this->im = im;
}

Complex::~Complex() {
	this->re = this->im = 0;
}

float Complex::abs() const {
	return sqrt(this->re * this->re + this->im * this->im);
}

Complex Complex::conj() const {
	return Complex(this->re, -this->im);
}

float Complex::phase() const {
	if (this->re > 0.f) {
		return atan2(this->im, this->re);
	} else if (this->re < 0.f) {
		return atan2(this->im, this->re) + PI;
	} else {
		if (this->im > 0.f) {
			return 0.5f * PI;
		} else if (this->im < 0.f) {
			return -0.5f * PI;
		}
    }
    return 0;
}

Complex Complex::operator-() const {
	return Complex(-this->re, -this->im);
}

Complex& Complex::operator+=(const Complex& other) {
	this->re += other.re;
	this->im += other.im;
	return *this;
}

Complex& Complex::operator-=(const Complex& other) {
	this->re -= other.re;
	this->im -= other.im;
	return *this;
}

Complex& Complex::operator*=(const Complex& other) {
	float temp_re = this->re;
	this->re = (this->re * other.re) + (-this->im * other.im);
	this->im = (this->im * other.re) + (temp_re * other.im);
	return *this;
}

Complex& Complex::operator/=(const Complex& other) {
	float temp_re = this->re;
	this->re = (this->re * other.re + this->im * other.im) / (other.re * other.re + other.im * other.im);
	this->im = (this->im * other.re - temp_re * other.im) / (other.re * other.re + other.im * other.im);
	return *this;
}

Complex& Complex::operator=(const Complex& other) {
	this->re = other.re;
	this->im = other.im;
	return *this;
}

Complex& Complex::operator=(float num) {
	this->re = num;
	this->im = 0.f;
	return *this;
}

Complex operator+(const Complex& first, const Complex& second) {
	return Complex(first.re + second.re, first.im + second.im);
}

Complex operator+(const Complex& first, float num) {
	return Complex(first.re + num, first.im);
}

Complex operator-(const Complex& first, const Complex& second) {
	return Complex(first.re - second.re, first.im - second.im);
}

Complex operator-(const Complex& first, float num) {
	return Complex(first.re - num, first.im);
}

Complex operator*(const Complex& first, const Complex& second) {
	return Complex(
		first.re * second.re + -first.im * second.im,
		first.im * second.re + first.re * second.im
	);
}

Complex operator/(const Complex& first, const Complex& second) {
	return Complex(
		(first.re * second.re + first.im * second.im) / (second.re * second.re + second.im * second.im),
		(first.im * second.re - first.re * second.im) / (second.re * second.re + second.im * second.im)
	);
}

std::ostream& operator<<(std::ostream& stream, const Complex& num) {
	stream << num.re;
	if (num.im != 0.f) {
		string sign = num.im < 0.f ? " - " : " + ";
		float num_value = num.im < 0.f ? -num.im : num.im;
		stream << sign << num_value << "i";
	}
	return stream;
}
