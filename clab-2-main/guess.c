#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number;
    unsigned int seed;

    int guesses = 0;

    printf("Enter a random seed: ");
    scanf("%u", &seed);
    srandom(seed);
    int randNum = random()%100 + 1;

    while (randNum != number) {
        printf("Guess a number: ");
        scanf("%i", &number);
        guesses++;
        if (number < randNum) {
            printf("Too low!\n");
        } else if (number > randNum){
            printf("Too high!\n");
        }
    } 
    printf("You got it! Total guesses = %i \n", guesses);

    return 0;
}