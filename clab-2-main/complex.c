
#include <stdio.h>

struct Complex {
    double real;
    double imaginary;
};

struct Complex multiplyComplex(struct Complex c1, struct Complex c2) {
    
    double realProduct = (c1.real * c2.real - c1.imaginary * c2.imaginary);
    double imaginaryProduct = (c1.real * c2.imaginary + c1.imaginary * c2.real);
    struct Complex c3;
    c3.real = realProduct;
    c3.imaginary = imaginaryProduct;
    return c3;
}

int main() {
    struct Complex c1;
    struct Complex c2;

    double realc1;
    double realc2;
    double imaginaryc1;
    double imaginaryc2;

    printf("Enter real part of c1: ");
    scanf("%lf", &realc1);
    c1.real = realc1;
    printf("Enter imaginary part of c1: ");
    scanf("%lf", &imaginaryc1);
    c1.imaginary = imaginaryc1;
    printf("Enter real part of c2: ");
    scanf("%lf", &realc2);
    c2.real = realc2;
    printf("Enter imaginary part of c2: ");
    scanf("%lf", &imaginaryc2);
    c2.imaginary = imaginaryc2;

    struct Complex c3 = multiplyComplex(c1, c2);
    printf("Answer = %10.2f + %10.2f i\n", c3.real, c3.imaginary);
    
    return 0;
}