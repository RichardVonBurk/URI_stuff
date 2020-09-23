#ifndef EXE_INCLUDED
#define EXE_INCLUDED

#include <stdint.h>
#include "mem_manager.h"

/**
 * Given a Mem_T with a program loaded into $m[0] and initialized
 * registers, this function will handle the execution of the
 * instruction set found in $m[0] until a HALT opcode is reached.
 * If the end of the instruction set is reached without a HALT
 * operation, the universal machine will exit with a non-zero
 * exit code.
 */
void execute_program(Mem_T segments, uint32_t *registers);

#endif