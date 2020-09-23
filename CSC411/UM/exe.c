#include <stdint.h>
#include <stdlib.h>
#include "assert.h"
#include "seq.h"
#include "exe.h"
#include "load.h"
#include "mem_manager.h"

/* OpCode defines for readability */
#define COND_MOVE 0
#define SEG_LOAD 1
#define SEG_STORE 2
#define ADD 3
#define MULTI 4
#define DIVIS 5
#define NAND 6
#define HALT 7
#define MAP_SEG 8
#define UNMAP_SEG 9
#define OUT 10
#define IN 11
#define LOAD_PROG 12
#define LOAD_VAL 13

/* Helper function prototypes */
void conditional_move(uint32_t *R, uint32_t a, uint32_t b, uint32_t c);
void add(uint32_t *R, uint32_t a, uint32_t b, uint32_t c);
void multiply(uint32_t *R, uint32_t a, uint32_t b, uint32_t c);
void divide(uint32_t *R, uint32_t a, uint32_t b, uint32_t c);
void bit_nand(uint32_t *R, uint32_t a, uint32_t b, uint32_t c);
void halt(Mem_T mem);
void output(uint32_t *R, uint32_t c);
void input(uint32_t *R, FILE *input, uint32_t c);
void exe_load_program(Mem_T mem, uint32_t *R, uint32_t b, uint32_t c);

void execute_program(Mem_T segments, uint32_t *registers)
{
  while (1) {
    uint32_t word, opcode, a, b, c, val;
    word = Mem_load_segment(segments, 0, segments->counter);
    uint32_t temp = word;
    opcode = temp >> 28;
    if (opcode == LOAD_VAL) {
      temp = word;
      temp = temp << 4;
      a = temp >> 29;
      temp = word;
      temp = temp >> 7;
      val = temp >> 7;
      registers[a] = val;
    } else {
      temp = word;
      temp = temp << 23;
      a = temp >> 29;
      temp = word;
      temp = temp << 26;
      b = temp >> 29;
      temp = word;
      temp = temp << 29;
      c = temp >> 29;
      
      switch(opcode) {
        case COND_MOVE:
          conditional_move(registers, a, b, c);
          break;

        case SEG_LOAD:
          registers[a] = Mem_load_segment(segments, registers[b], registers[c]);
          break;

        case SEG_STORE:
          Mem_store_segment(segments, registers[a], registers[b], registers[c]);
          break;

        case ADD:
          add(registers, a, b, c);
          break;

        case MULTI:
          multiply(registers, a, b, c);
          break;

        case DIVIS:
          divide(registers, a, b, c);
          break;

        case NAND:
          bit_nand(registers, a, b, c);
          break;

        case HALT:
          halt(segments);
          break;

        case MAP_SEG:
          registers[b] = Mem_map_segment(segments, registers[c]);
          break;

        case UNMAP_SEG:
          Mem_unmap_segment(segments, registers[c]);
          break;

        case OUT:
          output(registers, c);
          break;
        
        case IN:
          input(registers, stdin, c);
          break;

        case LOAD_PROG:
          exe_load_program(segments, registers, b, c);
          break;

      }
    }

    segments->counter++;
  }

}

void conditional_move(uint32_t *R, uint32_t a, uint32_t b, uint32_t c)
{
  if (R[c] != 0) {
    R[a] = R[b];
  }
}

void add(uint32_t *R, uint32_t a, uint32_t b, uint32_t c)
{
  R[a] = (R[b] + R[c]) % 4294967296;
}

void multiply(uint32_t *R, uint32_t a, uint32_t b, uint32_t c)
{
  R[a] = (R[b] * R[c]) % 4294967296;
}

void divide(uint32_t *R, uint32_t a, uint32_t b, uint32_t c)
{
 R[a] = R[b] / R[c];
}

void bit_nand(uint32_t *R, uint32_t a, uint32_t b, uint32_t c)
{
  R[a] = ~(R[b] & R[c]);
}

void halt(Mem_T mem)
{
  free_Mem(&mem);
  exit(0);
}

void output(uint32_t *R, uint32_t c)
{
  assert(R[c] < 256);
  putchar(R[c]);
}

void input(uint32_t *R, FILE *input, uint32_t c)
{
  uint32_t instruction = getc(input);
  if (instruction == (uint32_t) EOF) {
    instruction = -1;
  }
  R[c] = instruction;
}

void exe_load_program(Mem_T mem, uint32_t *R, uint32_t b, uint32_t c)
{
  if (R[b] != 0) {
    Seq_T temp = Seq_get(mem->segments, R[b]);
    uint32_t length = Seq_length(temp);
    Seq_T seg = Seq_new(length);
    for (uint32_t i = 0; i < length; i++) {
      add_instruction(seg, (uint32_t) (uintptr_t) Seq_get(temp, i));
    }
    Seq_put(mem->segments, 0, seg);
  }
  mem->counter = R[c] - 1;
}