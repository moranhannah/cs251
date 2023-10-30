/* Program demonstrating how to use printf */

#include <stdio.h> // required for printf

int main() {
    char c = 'a';
    int i = 5;
    long l = (1 << 16) + 1;
    float f = 42.67;
    double d = 109.2;
    char *s = "hello";
    int *p = &i; // more on the & and * symbols later
    int i1 = 15;
    int i2 = 87;

    printf("Here is an int %i and a char %c and a long %li\n", i, c, l);
    printf("and a float %f and a double %f\n", f, d);
    printf("and a string %s and a pointer %p\n", s, p);
    printf("and when you subtract %i from %i, you get %i\n", i1, i2, i2 - i1);

    return 0;
}