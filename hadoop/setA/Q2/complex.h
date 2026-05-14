#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    float real, imag;
} Complex;

Complex add_complex(Complex a, Complex b);
Complex mul_complex(Complex a, Complex b);

#endif
