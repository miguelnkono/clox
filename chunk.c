#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "memory.h"

void replaceCount(char *str, char *lineNum, char *newCount)
{
  char *lineStart = str;

  // Search for the line number, ensuring it's a complete number
  while ((lineStart = strstr(lineStart, lineNum)) != NULL) {
    // Check if this is a complete line number (not part of a larger number)
    // by verifying it's followed by '(' and potentially preceded by start of string or ')'
    char *afterNum = lineStart + strlen(lineNum);

    if (*afterNum == '(' &&
        (lineStart == str || *(lineStart - 1) == ')')) {
      break; // Found the correct line number
    }
    lineStart++; // Continue searching
  }

  if (lineStart == NULL) return;

  // Find the opening parenthesis after the line number
  char *openParen = strchr(lineStart, '(');
  if (openParen == NULL) return;

  openParen++; // Move past '('

  // Find the closing parenthesis
  char *closeParen = strchr(openParen, ')');
  if (closeParen == NULL) return;

  // Calculate positions
  int prefixLen = openParen - str;
  int oldCountLen = closeParen - openParen;

  // Replace the count
  memmove(openParen + strlen(newCount), closeParen, strlen(closeParen) + 1);
  memcpy(openParen, newCount, strlen(newCount));
}

void initChunk(Chunk *chunk)
{
  chunk->capacity = 0;
  chunk->count = 0;
  chunk->code = (uint8_t *)0;

  chunk->linesCount = 0;
  chunk->linesCapacity = 0;
  chunk->lines = (LineInfo *)0;

  initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
  // if there is not enough capacity left.
  if (chunk->count + 1 > chunk->capacity)
  {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;

  if (chunk->linesCount == 0) {
    // First instruction
    if (chunk->linesCapacity == 0) {
      chunk->linesCapacity = 8;
      chunk->lines = GROW_ARRAY(LineInfo, chunk->lines, 0, chunk->linesCapacity);
    }
    chunk->lines[0] = (LineInfo){0, line};
    chunk->linesCount = 1;
  } else {
    // Check if we're still on the same line as the last entry
    LineInfo *last = &chunk->lines[chunk->linesCount - 1];

    if (last->line == line) {
      // Same line - no need to add a new entry
      // The existing entry already covers this instruction
    } else {
      // Line changed - add new entry
      if (chunk->linesCount + 1 > chunk->linesCapacity) {
          int oldCapacity = chunk->linesCapacity;
          chunk->linesCapacity = GROW_CAPACITY(oldCapacity);
          chunk->lines = GROW_ARRAY(LineInfo, chunk->lines, oldCapacity, chunk->linesCapacity);
      }

      chunk->lines[chunk->linesCount] = (LineInfo){chunk->count, line};
      chunk->linesCount++;
    }
  }

  chunk->count++;
}

int getLine(Chunk *chunk, int instructionIndex)
{
  if (chunk->linesCount == 0 || instructionIndex < 0 || instructionIndex >= chunk->count) {
    return -1; // Invalid
  }

  // Simple linear search - acceptable since this is only called on errors
  for (int i = 0; i < chunk->linesCount; i++) {
    // If this is the last entry OR the next entry starts after our instruction
    if (i == chunk->linesCount - 1 || chunk->lines[i + 1].offset > instructionIndex) {
      return chunk->lines[i].line;
    }
  }

  return -1;
}

void freeChunk(Chunk *chunk)
{
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(LineInfo, chunk->lines, chunk->linesCapacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value)
{
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
