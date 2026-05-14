#include <math.h>
#include "math.h"

float absolute(Complex c) {
    return sqrt((c.real * c.real) + (c.imag * c.imag));
}

Complex power_complex(Complex c) {

    Complex res;

    // square of complex number
    res.real = (c.real * c.real) - (c.imag * c.imag);
    res.imag = 2 * c.real * c.imag;

    return res;
}