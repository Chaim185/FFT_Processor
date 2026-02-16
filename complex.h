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

int main() {
    // This computes FFT using Cooley-Tukey algorithm
    ComplexNumber W8(.7071, -.7071);

    int i; // to use in for loop
    int N = 8;
    int x[8] = { 1,2,12,-5,-4,8,-6,15 };
    int y[4], z[4];

    for (i = 0; i < 8; i = i + 2)
        y[i / 2] = x[i];
    for (i = 1; i < 8; i = i + 2)
        z[(i - 1) / 2] = x[i];

    int y_[2], y__[2], z_[2], z__[2];

    for (i = 0; i < 4; i = i + 2)
    {
        y_[i / 2] = y[i];
        z_[i / 2] = z[i];
    }

    for (i = 1; i < 4; i = i + 2)
    {
        y__[(i - 1) / 2] = y[i];
        z__[(i - 1) / 2] = z[i];
    }

    double a, b, c, d, e, f, g, h;

    a = y_[0];
    b = y_[1];
    c = y__[0];
    d = y__[1];
    e = z_[0];
    f = z_[1];
    g = z__[0];
    h = z__[1];

    ComplexNumber A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h);



    ComplexNumber Y_[2], Y__[2], Z_[2], Z__[2];
    ComplexNumber W4 = W8.power(2);
    ComplexNumber W2 = W4.power(2);


    for (i = 0; i < 2; i = i + 1)
    {
        Y_[i] = A.add(B.multiply(W2.power(i)));
        Y__[i] = C.add(D.multiply(W2.power(i)));
        Z_[i] = E.add(F.multiply(W2.power(i)));
        Z__[i] = G.add(H.multiply(W2.power(i)));
    }

    ComplexNumber Y[4], Z[4];

    for (i = 0; i < 4; i = i + 1)
    {
        if (i < 2)
        {
            Y[i] = Y_[i].add(Y__[i].multiply(W4.power(i)));
            Z[i] = Z_[i].add(Z__[i].multiply(W4.power(i)));
        }
        else
        {
            Y[i] = Y_[i - 2].add(Y__[i - 2].multiply(W4.power(i)));
            Z[i] = Z_[i - 2].add(Z__[i - 2].multiply(W4.power(i)));
        }
    }


    ComplexNumber X[8];

    for (i = 0; i < 8; i = i + 1)
    {
        if (i < 4)
            X[i] = Y[i].add(Z[i].multiply(W8.power(i)));
        else
            X[i] = Y[i - 4].add(Z[i - 4].multiply(W8.power(i)));
    }

    for (i = 0; i < 8; i++)
    {
        cout << "X[" << i << "] is ";
        X[i].display();
        cout << endl;
    }

    return 0;
}

