#include <stddef.h>
#include "uarray2.h"
#include "array.h"
#include "arrayrep.h"
#include "assert.h"
#include "mem.h"
#include "bit.h"
#include "bit2.h"

/**
 * This file is a two dimentional struc of an Array_T which at each iteration stores the struc Bit_T
 * This can only use bits
*/

#define T Bit2_T
struct T
{
    int width;
    int height;
    Array_T rows;
};

T Bit2_new(int width, int height){
    assert(width>0);
    assert(height>0);

    T bit2;
    NEW(bit2);
    //create the 'main' array (bit2->rows) which dimensions are arbitrarily called width
    bit2 -> rows = Array_new(width , sizeof(Array_T));
    //add a Bit_T of length 'height' at each iteration of the 'main' array
    for (int i=0; i<width; i++){
        Bit_T* row_p = Array_get(bit2->rows,i);
        *(row_p) = Bit_new(height);
    }
    bit2->width = width;
    bit2->height = height; 
    return bit2; 
}
void Bit2_free(T* bit2){
    assert(bit2);
    FREE((*bit2)->rows);
    FREE(*bit2);

}
int Bit2_width(T bit2){
    assert(bit2);
    return bit2->width;
}
int Bit2_height(T bit2){
    assert(bit2);
    return bit2->height;
}
int Bit2_get(T bit2, int row, int col){
    assert(bit2);
    assert(row >= 0 && col >= 0 );
    assert(row < bit2-> width && col < bit2->height);
    //return statement explained: cast Array_get(bit2->rows at row#) to Array_T, dereference that to a Bit_T,
    //then use Bit_get to get bit at col#
    return Bit_get(*((Bit_T*)Array_get(bit2->rows, row)), col);
}
int Bit2_put(T bit2, int row, int col, int bit){
    assert(bit2);
    assert(row >= 0 && col >= 0 );
    assert(row < bit2-> width && col < bit2->height);
    //return statement explained: cast Array_get(bit2->rows at row#) to Array_T, dereference that to a Bit_T,
    //then use Bit_put to change the bit at col# to our vairable 'bit'
    return Bit_put(*((Bit_T*)Array_get(bit2->rows, row)), col, bit);
}

void Bit2_map_row_major(T bit2, void Apply(T bit2, int row, int col, void* cl), void* cl)
{
    assert(bit2);
    for (int i=0; i<bit2->width; i++)
    {
        for (int j=0; j<bit2->height; j++)
        {
            Apply(bit2, i, j, cl);
        }
    }
}


void Bit2_map_col_major(T bit2, void Apply(T bit2, int row, int col, void* cl), void* cl)
{
    assert(bit2);
    for (int j=0; j<bit2->height; j++)
    {
        for (int i=0; i<bit2->width; i++)
        {
            Apply(bit2, i, j, cl);
        }
    }
}