#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "linkedlist.h"
#include "value.h"
#include "talloc.h"

// Create a new NULL_TYPE value node.
Value *makeNull(){
   Value *newValue = talloc(sizeof(Value));
   newValue->type = NULL_TYPE;
   return newValue;
}


// Create a new CONS_TYPE value node.
Value *cons(Value *newCar, Value *newCdr){
   Value *newCell = talloc(sizeof(Value));
   newCell->type = CONS_TYPE;
   newCell->c.car = newCar;
   newCell->c.cdr = newCdr;
   return newCell;
}


// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list){
    if (list->type != NULL_TYPE) {
        switch (list->type) {
        case OPENBRACKET_TYPE:
            break;
        case CLOSEBRACKET_TYPE:
            break;
        case DOT_TYPE:
            break;
        case SINGLEQUOTE_TYPE:
            break;
        case PTR_TYPE:
            printf("Int type: %p\n", list->p);
            break;
        case INT_TYPE:
            printf("Int type: %i\n", list->i);
            break;
        case DOUBLE_TYPE:
            printf("Double type: %lf\n", list->d);
            break;
        case STR_TYPE:
            printf("String type: %s\n", list->s);
            break;
        case NULL_TYPE:
            printf("Null type\n");
            break;
        case OPEN_TYPE:
        printf("Open type: %s\n", list->s);
        break;
        case CLOSE_TYPE:
        printf("Close type: %s\n", list->s);
        break;
        case BOOL_TYPE:
        printf("Bool type: %s\n", list->s);
        break;    
        case SYMBOL_TYPE:
        printf("Symbol type: %s\n", list->s);
        break; 
        
        case CONS_TYPE:
            display(list->c.car);
            display(list->c.cdr);
            break;
        }
    }
}


// Return a new list that is the reverse of the one that is passed in. No stored
// data within the linked list should be duplicated; rather, a new linked list
// of CONS_TYPE nodes should be created, that point to items in the original
// list.
Value *reverse(Value *list) {
    if (isNull(list)) {
	    return makeNull();
    }
    Value *newList = makeNull();
    //Value *temp = list;

    while(!isNull(list)) {
        newList = cons(car(list), newList);
        list = list->c.cdr;
    }
    return newList;
}
// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value) {
   if (value->type == NULL_TYPE) {
       return true;
   } else {
       return false;
   }
}

// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list) {
   return list->c.car;
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list) {
   return list->c.cdr;
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value) {
   if (value->type == NULL_TYPE) return 0;
   int count = 0;
   Value *curr = value;

   while(curr != NULL && !isNull(curr)) {
    curr = cdr(curr);
    count++;
   }
   return count;
}


