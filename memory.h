//
// Created by Nkono Ndeme Miguel on 24/08/2025.
//

#ifndef LOX_MEMORY_H
#define LOX_MEMORY_H

// this module is for memory usage.

#include "common.h"

// macro for growing the capacity of a chunk of data.
// here we could grow by a facto of 1.5 but 2 is good for us.
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

// macro to grow the array if bytecode.
#define GROW_ARRAY(type, pointer, oldCapacity, newCapacity) \
    (type*)reallocate(pointer, sizeof(type) * (oldCapacity), \
        sizeof(type) * (newCapacity))

// macro to free the array of bytecode. Since the newSize argument of the reallocate helper is set to zero it will free
// the block of memory.
#define FREE_ARRAY(type, pointer, oldCapacity) \
    reallocate(pointer, sizeof(type) * (oldCapacity), 0)

// wrapper around the realloc standard function.
// this helper function will act like this:
//      * if the oldSize is zero                            -> allocate new block
//      * if the newSize is zero                            -> free the block
//      * if the oldSize is greater than the newSize        -> shrink the existing allocation
//      * if the oldSize is lesser than the newSize         -> grow the existing allocation
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif //LOX_MEMORY_H