//
// Created by Nkono Ndeme Miguel on 24/08/2025.
//

#include "memory.h"

#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    // if the newSize is zero, we free the memory.
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    // attempt to grow the block of memory, if it fails we exit the entire program but if it succeeds we return a pointer
    // to the newly allocated block.
    void *result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}
