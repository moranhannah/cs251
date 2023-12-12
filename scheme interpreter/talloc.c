#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"
#include <assert.h>
#include <string.h>
#include "talloc.h"
#include "value.h"

typedef struct Value Value;

Value *activeList; 

void *talloc(size_t size) {
  if (activeList == NULL) {
      Value *null = malloc(sizeof(Value));
      null->type = NULL_TYPE;
      activeList = null;
  }

  Value *newPointer = malloc(sizeof(Value)); 
  newPointer->type = PTR_TYPE;
  void *newVal = malloc(size);
  newPointer->p = newVal;

  Value *newCons = malloc(sizeof(Value));
  newCons->type = CONS_TYPE;

  newCons->c.car = newPointer;
  newCons->c.cdr = activeList;

  activeList = newCons;

  return newVal;
}

void tfree() {
  
  Value *temp = activeList;

  while (activeList != NULL && !isNull(activeList)) {
    if (activeList->c.car != NULL && activeList->c.car->type == PTR_TYPE) {
      free(activeList->c.car->p);
    }
    free(activeList->c.car);
    temp = activeList;
    activeList = activeList->c.cdr;
    free(temp);
  }

  free(activeList);
  activeList = NULL;
}

void texit(int status) {
  tfree();
  exit(status);
}