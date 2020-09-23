#ifndef MEM_MANAGER_INCLUDED
#define MEM_MANAGER_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "seq.h"
#include "stack.h"

typedef struct Mem_T {
  Seq_T segments;
  Stack_T unmapped;
  int counter;
} *Mem_T;

Mem_T Mem_new(Seq_T program, unsigned num_segments);

void free_Mem(Mem_T *mem);

void Mem_store_segment(Mem_T mem, uint32_t reg_a, uint32_t reg_b, uint32_t val);

uint32_t Mem_map_segment(Mem_T mem, uint32_t num_segments);

void Mem_unmap_segment(Mem_T mem, uint32_t index);

uint32_t Mem_load_segment(Mem_T mem, uint32_t reg_b, uint32_t reg_c);

void Mem_load_program(Mem_T mem, Seq_T program);

void add_instruction(Seq_T program, uint32_t instruction);

#endif