#include "complex.h"

Complex add_complex(Complex a, Complex b){
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

Complex mul_complex(Complex a, Complex b){
    Complex c;
    c.real = (a.real*b.real) - (a.imag*b.imag);
    c.imag = (a.real*b.imag) + (a.imag*b.real);
    return c;
}