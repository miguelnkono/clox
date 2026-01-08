#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "value.h"

static inline int simpleInstruction(const char *name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static inline int constantInstruction(const char *name, Chunk *chunk,
                                      int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

// Helper function to get line number for display
static int getLineForDisplay(Chunk *chunk, int offset) {
  // Simple linear search through the run-length encoded lines
  for (int i = 0; i < chunk->linesCount; i++) {
    // If this is the last entry OR the next entry starts after our offset
    if (i == chunk->linesCount - 1 || chunk->lines[i + 1].offset > offset) {
      return chunk->lines[i].line;
    }
  }
  return -1; // Should not happen for valid offsets
}

int disassembleInstruction(Chunk *chunk, int offset) {
  printf("%04d ", offset);

  int currentLine = getLineForDisplay(chunk, offset);
  int previousLine = (offset > 0) ? getLineForDisplay(chunk, offset - 1) : -1;

  if (offset > 0 && currentLine == previousLine) {
    printf("   | ");
  } else {
    printf("%4d ", currentLine);
  }

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  case OP_NEGATE:
    return simpleInstruction("OP_NEGATE", offset);
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  default:
    printf("unknown opcode %d\n", instruction);
    return offset + 1;
  }
}
