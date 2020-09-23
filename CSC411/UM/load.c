#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "seq.h"
#include "mem_manager.h"
#include "load.h"
#include "bitpack.h"
#include <sys/stat.h>

/* Helper function prototypes */
uint32_t get_instruction(FILE *fileptr, int a);
void check_file_format(int size);
int get_file_size(char *filename);

Mem_T load_program(FILE *fileptr, char *filename)
{
  int file_size = get_file_size(filename);
  check_file_format(file_size);
  Seq_T program = Seq_new(file_size / 4);
  int a;
  while ((a = getc(fileptr)) != EOF) {
    add_instruction(program, get_instruction(fileptr, a));
  }

  Mem_T memory = Mem_new(program, 4);
  return memory;
}

uint32_t get_instruction(FILE *fileptr, int a)
{
  uint64_t word = 0;
  int b = getc(fileptr);
  int c = getc(fileptr);
  int d = getc(fileptr);
  word = Bitpack_newu(word, 8, 24, a);
  word = Bitpack_newu(word, 8, 16, b);
  word = Bitpack_newu(word, 8, 8, c);
  word = Bitpack_newu(word, 8, 0, d);
  return (uint32_t) word;
}

void check_file_format(int size)
{
  if (size % 4 != 0 || size == 0) {
    fprintf(stderr, "Incorrect file format\n");
    exit(EXIT_FAILURE);
  }
}

int get_file_size(char *filename) {
  struct stat info;
  stat(filename, &info);
  return info.st_size;
}