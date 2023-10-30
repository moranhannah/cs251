#include <stdio.h>
#include <stdlib.h>

struct Vector
{
    int* array;

    int memorySize;

    int size;
};

typedef struct Vector Vector;

void init(Vector *vector, int memorySize) {
    // initialize the vector
    vector->memorySize = memorySize;
    vector->size = 0;
    vector->array = malloc(sizeof(int) * memorySize);
}

void cleanup(Vector *vector) {
    // deallocates the memory
    free(vector->array);
}

void print(Vector *vector) {
    // prints each element in the vector
    for ( int j=0 ; j < vector->size ; j++ ) {
        printf("%d\n", vector->array[j]);
    }
}

int insert(Vector *vector, int location, int value) {
    // check if location is valid
    if (location < 0 || location > vector->size) {
        return 0;
    } 
    
    // if valid...
    if (vector->size >= vector->memorySize) {
        // create new array
        int newArray[vector->size];
        for (int j=0; j < vector->size; j++) {
            newArray[j] = vector->array[j];
        }

        // deallocate old array
        free(vector->array);
        // instatiate new array with larger allocation of memory
        vector->array = malloc(2 * sizeof(int) * vector->memorySize);
        vector->memorySize = 2 * vector->memorySize;

        // fill new array
        for ( int j=0 ; j<vector->size ; j++ ) {
            vector->array[j] = newArray[j];
        }
    } 

    for ( int j=vector->size ; j > location ; j--) {
        vector->array[j] = vector->array[j-1];
    } 

    // new vector with new value
    vector->size++;
    vector->array[location] = value;
    return 1;
}

int get(Vector *vector, int location, int *value) {
    // check if location is valid and find if the value exists
    if (location < vector->size && location >= 0) {
        *value = vector->array[location];
        return 1;
    }
    return 0;
}

int delete(Vector *vector, int location) {
    //check if location is valid
    if (location < 0 || location >= vector->size + 1) {
        return 0;
    }

    // if yes, shift values
    for (int j=location; j <= vector->size; j++) {
        vector->array[j] = vector->array[j+1];
    }
    vector->size--;
    return 1;
}