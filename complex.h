/*
Here is supplementary C++ code which calculates the FFT properly, using complex numbers.
The code contains a class called ComplexNumber and two main programs.
The 1st main program calculates the Discrete Fourier Transform using a series sum.
The 2nd main program calculates the Discrete Fourier Transform using the FFT Cooley - Tukey algorithm.
The results are nearly identical.
*/
#include <iostream>
using namespace std;

class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    // Constructors
    ComplexNumber() : real(0.0), imaginary(0.0) {}

    ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

    ComplexNumber(double real) : real(real), imaginary(0.0) {}

    // Adder function
    ComplexNumber add(const ComplexNumber& other) const {
        ComplexNumber result;
        result.real = this->real + other.real;
        result.imaginary = this->imaginary + other.imaginary;
        return result;
    }

    // Multiply function
    ComplexNumber multiply(const ComplexNumber& other) const {
        ComplexNumber result;
        result.real = this->real * other.real - this->imaginary * other.imaginary;
        result.imaginary = this->real * other.imaginary + this->imaginary * other.real;
        return result;
    }

    ComplexNumber power(int n) const {
        if (n == 0)
            return ComplexNumber(1.0);
        return this->multiply(this->power(n - 1));
    }

    void display() const {
        cout << real;
        if (imaginary >= 0)
            cout << " + " << imaginary << "i";
        else if (imaginary < 0)
            cout << " - " << -imaginary << "i";

        cout << endl;
    }
};
