#ifndef LOAD_INCLUDED
#define LOAD_INCLUDED

#include <stdio.h>
#include "mem_manager.h"

/**
 * Given a pointer to an opened .um binary file,
 * this function will return a Hanson's Seq_T, representing 
 * $m[0] in segmented memory with the program in the .um loaded.
 */
Mem_T load_program(FILE *fileptr, char *filename);

#endif