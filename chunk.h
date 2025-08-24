//
// Created by Nkono Ndeme Miguel on 24/08/2025.
//

#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

// this module is to define our code representation.
// typically how we are going to represent one bytecode instruction (one chunk).

#include "common.h"

// this will represent what kind of operation each bytecode instruction does. It is generally call 'operation code' so
// we abbreviate that to 'OpCode'.
// it will control what kind of instruction we're dealing with right now.
typedef enum {
    OP_RETURN,      // represent a return type bytecode.
} OpCode;

// this will represent our chunk of bytecode.
// it is a dynamic array.
typedef struct  {
    int count;      // the number of entities allocated are in used.
    int capacity;   // the number of elements in the array we have allocated.
    uint8_t* code;  // the array of bytecode for one chunk.
} Chunk;

// constructor for a chunk.
void initChunk(Chunk *chunk);
// append a byte to the end of the chunk.
void writeChunk(Chunk *chunk, uint8_t byte);
// freeing the memory used by a chunk.
void freeChunk(Chunk *chunk);

#endif //LOX_CHUNK_H