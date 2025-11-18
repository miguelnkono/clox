#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// the operation code.
typedef enum
{
  OP_CONSTANT, // produces a particular constant.
  OP_RETURN,   // operation to return from the current function.
} OpCode;

typedef struct
{
  int offset;
  int line;
} LineInfo;

// the bytecode instructions.
typedef struct
{
  int count;            // number of operation instructions in used.
  int capacity;         // the number of bytecode operation.
  uint8_t *code;        // chunk of bytecode.

  LineInfo *lines;           // line number of each bytecode instruction.
  int linesCount;
  int linesCapacity;

  ValueArray constants; // constant pool of a chunk.
} Chunk;

void initChunk(Chunk *chunk);                // initialize a chunk.
void freeChunk(Chunk *chunk);                // free the chunk.
void writeChunk(Chunk *chunk, uint8_t byte, int line); // write a byte into the chunk.
int addConstant(Chunk *chunk, Value value);  // return the location where the constant was added.
int getLine(Chunk *chunk, int instructionIndex);

#endif // clox_chunk_h
