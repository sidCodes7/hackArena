#include <stdio.h>
#include "complex.h"

int main() {
    Complex a = {2, 3};
    Complex b = {4, 5};

    Complex sum = add_complex(a, b);
    Complex mul = mul_complex(a, b);

    printf("Addition: %.1f + %.1fi\n", sum.real, sum.imag);
    printf("Multiplication: %.1f + %.1fi\n", mul.real, mul.imag);

    return 0;
}