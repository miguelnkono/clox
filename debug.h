//
// Created by Nkono Ndeme Miguel on 24/08/2025.
//

#ifndef LOX_DEBUG_H
#define LOX_DEBUG_H
#include "chunk.h"

// disassemble a chunk typically a bytecode so that we could inspect it.
void disassemble(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);

#endif //LOX_DEBUG_H