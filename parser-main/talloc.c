#include <stdio.h>
#include <stdlib.h>
#include "talloc.h"
#include <stdbool.h>
//#include "linkedlist.c"


Value *global_list = NULL;

// Replacement for malloc that stores the pointers allocated. It should store
// the pointers in some kind of list; a linked list would do fine, but insert
// here whatever code you'll need to do so; don't call functions in the
// pre-existing linkedlist.h. Otherwise you'll end up with circular
// dependencies, since you're going to modify the linked list to use talloc.
void *talloc(size_t size) {
    Value *newPtr = malloc(sizeof(Value) * size);
    Value *tempGlobal = malloc(sizeof(Value));
    tempGlobal->type = CONS_TYPE;
    tempGlobal->c.car = newPtr;
    tempGlobal->c.cdr = global_list;
    global_list = tempGlobal;

    return newPtr;

}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated in lists to hold those pointers.
void tfree() {
    if (global_list == NULL){
        return;
    } 

    while (global_list != NULL) {
        Value *currentRemove = global_list;
        global_list = currentRemove->c.cdr;
        free(currentRemove->c.car);
        free(currentRemove);
    }
    free(global_list);
}

// Replacement for the C function "exit", that consists of two lines: it calls
// tfree before calling exit. It's useful to have later on; if an error happens,
// you can exit your program, and all memory is automatically cleaned up.
void texit(int status) {
    tfree();
    exit(status);
}


