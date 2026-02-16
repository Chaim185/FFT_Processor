#include "complex.h"

int main() {
    // Computes DFT using a series sum
    int i, k, n;
    ComplexNumber sum;
    ComplexNumber WN(.7071, -.7071);
    int N = 8;
    ComplexNumber x[N] = { 1.0,2.0,12.0,-5.0,-4.0,8.0,-6.0,15.0 };

    ComplexNumber X[N];

    for (k = 0; k < N; k++)
    {
        sum.setReal(0.0);
        sum.setImaginary(0.0);
        for (n = 0; n < N; n++)
        {
            sum = sum.add(x[n].multiply(WN.power(k * n)));
        }
        X[k] = sum;
    }

    for (i = 0; i < N; i++)
    {
        cout << "X[" << i << "] is ";
        X[i].display();
        cout << endl;
    }
    return 0;
}