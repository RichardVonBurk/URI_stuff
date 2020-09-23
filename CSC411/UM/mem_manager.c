#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mem_manager.h"
#include "stack.h"
#include "seq.h"
#include "assert.h"
#include "mem.h"

Mem_T Mem_new(Seq_T program, unsigned num_segments)
{
  Mem_T mem;
  NEW(mem);
  assert(mem);
  mem->segments = Seq_new(num_segments);
  assert(mem->segments);
  Seq_addlo(mem->segments, (void*) program);
  mem->unmapped = Stack_new();
  mem->counter = 0;
  return mem;
}

void free_Mem(Mem_T *mem)
{
  assert(mem);
  int length = Seq_length((*mem)->segments);
  for (int i = 0; i < length; i++) {
    Seq_free(Seq_get((*mem)->segments, i));
  }
  Seq_free(&((*mem)->segments));
  Stack_free(&((*mem)->unmapped));
  free(*mem);
}

void Mem_store_segment(Mem_T mem, uint32_t reg_a, uint32_t reg_b, uint32_t val)
{
  assert(mem);
  Seq_T segment = (Seq_T) Seq_get(mem->segments, reg_a);
  Seq_put(segment, reg_b, (void*) (uintptr_t) val);
}

uint32_t Mem_map_segment(Mem_T mem, uint32_t num_segments)
{
  assert(mem);
  Seq_T segment = Seq_new(num_segments);
  for (uint32_t i = 0; i < num_segments; i++) {
    Seq_addhi(segment, (void*) (uintptr_t) 0);
  }
  uint32_t index;
  if (Stack_empty(mem->unmapped) == 1) {
    Seq_addhi(mem->segments, (void*) segment);
    index = Seq_length(mem->segments) - 1;
  } else {
    index = (int) (uintptr_t) Stack_pop(mem->unmapped);
    Seq_free(Seq_put(mem->segments, index, (void*) segment));
  }
  return index;
}

void Mem_unmap_segment(Mem_T mem, uint32_t index)
{
  assert(mem);
  Stack_push(mem->unmapped, (void*) (uintptr_t) index);
}

uint32_t Mem_load_segment(Mem_T mem, uint32_t reg_b, uint32_t reg_c)
{
  assert(mem);
  Seq_T segment = (Seq_T) Seq_get(mem->segments, reg_b);
  return (uint32_t) (uintptr_t) Seq_get(segment, reg_c);
}

void Mem_load_program(Mem_T mem, Seq_T program)
{
  (void) mem;
  (void) program;
}

void add_instruction(Seq_T program, uint32_t instruction)
{
  Seq_addhi(program, (void*) (uintptr_t) instruction);
}