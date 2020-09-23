#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "load.h"
#include "exe.h"
#include "mem_manager.h"

int main(int argc, char *argv[])
{
  /* Main assertions and file opening */
  assert(argc == 2);
  FILE *fileptr = fopen(argv[1],"r");
  assert(fileptr);
  /* load program in a Seq_T */
  Mem_T program = load_program(fileptr, argv[1]);
  fclose(fileptr);
  /* create registers and execute loaded program */
  uint32_t registers[8] = {0};
  execute_program(program, registers);
  exit(0);
}