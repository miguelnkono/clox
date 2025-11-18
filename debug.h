#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disambleChunk(Chunk *chunk, const char *name);
int disambleInstruction(Chunk *chunk, int offset);

#endif // clox_debug_h
