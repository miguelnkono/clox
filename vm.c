
#include "vm.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>

// this is just for convenience but it'll be better if we pass a pointer of VM
VM vm;

// we initialize the stackTop to point to the stack array.
// any operations made through the stackTop will be applied to the stackTop
// array.
static void resetStack() { vm.stackTop = vm.stack; }

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("                    ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_NEGATE:
      push(-pop());
      break;
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

void initVM() { resetStack(); }

InterpretResult interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

void freeVM() {}

void push(Value value) {
  // we store the 'value' onto the array and increment to the next position.
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}
