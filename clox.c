#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // Add several instructions from the same line
  uint8_t constant_idx = addConstant(&chunk, 1.2);
  writeChunk(&chunk, constant_idx, 123);
  // writeChunk(&chunk, OP_NEGATE, 124);

  // Add instructions from different lines
  writeChunk(&chunk, OP_RETURN, 125);

  // disassembleChunk(&chunk, "test chunk");

  interpret(&chunk);

  freeVM();
  freeChunk(&chunk);
  return 0;
}
