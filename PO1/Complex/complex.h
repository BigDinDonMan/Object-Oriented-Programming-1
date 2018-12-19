#ifndef COMPLEX_H
#define COMPLEX_H
#define PI 3.141592

class Complex {
    private:
        float re;
        float im;
    public:
        Complex(float re = 0.f, float im = 0.f);
        ~Complex();

        float abs() const;
        Complex conj() const;
        float phase() const;

        Complex& operator+=(const Complex& other);
        Complex& operator-=(const Complex& other);
        Complex& operator*=(const Complex& other);
        Complex& operator/=(const Complex& other);
        Complex& operator=(const Complex& other);
        Complex operator-() const;
        Complex& operator=(float num);

        friend std::ostream& operator<<(std::ostream& stream, const Complex& num);
        friend Complex operator+(const Complex& first, const Complex& second);
        friend Complex operator+(const Complex& first, float num);
        friend Complex operator-(const Complex& first, float num);
        friend Complex operator-(const Complex& first, const Complex& second);
        friend Complex operator*(const Complex& first, const Complex& second);
        friend Complex operator/(const Complex& first, const Complex& second);
 };

#endif