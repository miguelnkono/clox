#include "common.h"
#include "chunk.h"
#include "debug.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
  Chunk chunk;
  initChunk(&chunk);

  // Add several instructions from the same line
  int constant = addConstant(&chunk, 1.2);
  for (int i = 0; i < 10; i++) {
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
  }

  // Add instructions from different lines
  writeChunk(&chunk, OP_RETURN, 124);
  writeChunk(&chunk, OP_RETURN, 125);

  disassembleChunk(&chunk, "test chunk");

  printf("Total instructions: %d\n", chunk.count);
  printf("Line entries: %d\n", chunk.linesCount); // Should be much smaller than chunk.count

  freeChunk(&chunk);
  return 0;
}
