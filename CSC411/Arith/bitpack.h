#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "except.h"
extern bool Bitpack_fitsu(uint64_t n, unsigned width);
extern bool Bitpack_fitss( int64_t n, unsigned width);
extern uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb);
extern int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb);
extern uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value);
extern uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t value);
extern Except_T Bitpack_Overflow;
#endif

