
#include <corecrt_startup.h>

#include "chunk.h"
#include "debug.h"
#include "common.h"

// The entry of our interpreter.
int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_RETURN, 123);

    int constant2 = addConstant(&chunk, 2.8);
    writeChunk(&chunk, OP_CONSTANT, 124);
    writeChunk(&chunk, constant2, 124);

    disassemble(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
