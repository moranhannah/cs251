#include <stdio.h>

int main () {
    float temp_f;
    float temp_c;
    printf("Please enter the temperature in Fahrenheit: ");
    scanf("%f", &temp_f);
    
    if (temp_f <= -459.67) {
        printf("Invalid temperature.\n");
    } else {
        temp_c = (temp_f - 32) * 5/9;
        printf("That is %f degrees Celcius.\n", temp_c); 
    }
    return 0;
}