/* Program demonstrating arrays in C. */

#include <stdio.h>

int main() {
    int x = 0;
    int array[10];
    int i;

    // Writing the elements of an array
    for (i = 0; i < 10; i++) {
        array[i] = i;
    }

    // Reading from an array
    for (i = 0; i < 10; i++) {
        printf("%i ", array[i]);
    }
    printf("\n");

    // Writing past the array results in weirdness;
    printf("x value before writing to array[10]: %i\n", x);
    
    printf("x value after writing to array[10]: %i\n", x);

    // Using pointer arithmetic to access the elements of an array
    printf("Array address: %p\n", array);
    for (i = 0; i < 10; i++) {
        printf("Array element at address %p: %i\n", array + i, *(array + i));
    }
    
    // total sum of the array
    int total;
    for (i = 0; i < 10; i++) {
        total = total + array[i];
    }
    printf("The sum of this array is: %i\n", total);
}