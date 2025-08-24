//
// Created by Nkono Ndeme Miguel on 24/08/2025.
//

#ifndef LOX_VALUE_H
#define LOX_VALUE_H

// this represents how we represent value in our interpreter.

#include "common.h"

typedef double Value;

// this is the constant pool aims to store constants.
typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);                 // initialize the pool array.
void writeValueArray(ValueArray *array, Value value);   // write a value in the pool array.
void freeValueArray(ValueArray *array);                 // free the constant pool array.
void printValue(Value value);

#endif //LOX_VALUE_H