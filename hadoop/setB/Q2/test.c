#include <stdio.h>
#include "math.h"

int main() {

    Complex c = {3,4};

    float abs_val = absolute(c);

    Complex p = power_complex(c);

    printf("Absolute Value = %.2f\n", abs_val);

    printf("Power Result = %.2f + %.2fi\n",
    p.real, p.imag);

    return 0;
}