#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

// the operation code.
typedef enum
{
  OP_RETURN, // operation to return from the current function.
} OpCode;

// the bytecode instructions.
typedef struct
{
  int count;     // number of operation instructions in used.
  int capacity;  // the number of bytecode operation.
  uint8_t *code; // chunk of bytecode.
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte);

#endif // clox_chunk_h
