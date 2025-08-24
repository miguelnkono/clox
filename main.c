
#include "chunk.h"
#include "debug.h"
#include "common.h"

// The entry of our interpreter.
int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);

    disassemble(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
