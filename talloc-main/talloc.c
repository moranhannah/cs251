#include <stdio.h>
#include <stdlib.h>
#include "talloc.h"
#include "linkedlist_talloc.c"


Value *global_list = NULL;


void talloc() {
    value *newPtr = malloc(sizeof(Value));
    Value *tempGlobal = malloc(sizeof(Value));
    tempGlobal->type = CONS_TYPE;
    tempGlobal->c.car = newPtr;
    tempGlobal->c.cdr = globalList;
    global_list = tempGlobal;

    return newPtr;

}
