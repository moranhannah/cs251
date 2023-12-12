#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"
#include <assert.h>
#include <string.h>
#include "talloc.h"

typedef struct Value Value;

Value *car(Value *list) {
  return list->c.car;
}

Value *cdr(Value *list) {
  return list->c.cdr;
}

Value *makeNull() {
  Value *null = talloc(sizeof(Value));
  null->type = NULL_TYPE;
  return null;
}

Value *cons(Value *newCar, Value *newCdr) {
  Value *newCons = talloc(sizeof(Value));
  newCons->type = CONS_TYPE;
  newCons->c.car = newCar;
  newCons->c.cdr = newCdr;
  return newCons;
}

void display(Value *list) {
  if (list->type != NULL_TYPE) {
    switch (list->type) {
    case INT_TYPE:
        printf("Int: %i\n", list->i);
        break;
    case DOUBLE_TYPE:
        printf("Double: %lf\n", list->d);
        break;
    case STR_TYPE:
        printf("String: %s\n", list->s);
        break;
    case NULL_TYPE:
        printf("Null type\n");
        break;
    case PTR_TYPE:
         printf("String: %p\n", list->p);
        break;
    case OPEN_TYPE:
        printf("Open type\n");
        break;                   
    case CLOSE_TYPE:
        printf("Close type\n");
        break;                   
    case BOOL_TYPE:
        printf("Boolean type\n");                 
        break;                   
    case SYMBOL_TYPE:
        printf("Symbol type\n");
        break;                   
    case CONS_TYPE:
        printf("Cons type\n");
        display(list->c.car);
        display(list->c.cdr);
        break;
    case OPENBRACKET_TYPE:
        printf("Open Bracket type\n");
        break; 
    case CLOSEBRACKET_TYPE:
      printf("Close Bracket type\n");
      break; 
    case DOT_TYPE:
      printf("Dot type\n");
      break; 
    case SINGLEQUOTE_TYPE:
      printf("Single Quote type\n");
      break; 
    case VOID_TYPE:
      printf("Void type\n");
      break;
    case CLOSURE_TYPE:
      printf("Closure type\n");
      break;
    case PRIMITIVE_TYPE:
      printf("Primitive type\n");
      break;
    case UNSPECIFIED_TYPE:
      break;
    }
  }
}


Value *reverse(Value *list) {
  if (list->type == NULL_TYPE) return makeNull();
  Value *newlist = makeNull();

  while (list != NULL && !isNull(list)) {
    newlist = cons(car(list), newlist);
    list = list->c.cdr;
  }
  return newlist;
}

bool isNull(Value *value) {
  if (value->type == NULL_TYPE) {
   return true;
  }
  else return false;
}

int length(Value *value) {
  if (value->type == NULL_TYPE) return 0;
  int count = 0;
  Value *curr = value;

  while (curr != NULL && !isNull(curr)) {
    curr = cdr(curr);
    count++;
  }

  return count;
}