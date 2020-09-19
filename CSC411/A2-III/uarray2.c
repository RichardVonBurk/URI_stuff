#include <stddef.h>
#include <stdio.h>
#include "uarray2.h"
#include "array.h"
#include "arrayrep.h"
#include "assert.h"
#include "mem.h"

/**
 * This file is a two dimentional struc of an Array_T which at each iteration stores a struc Array_T
 * UArray2 elements are not defined and therefore UArray2 can be used with a lot data types
*/

#define T UArray2_T

struct T
{
    int width;
    int height;
    int size;
    Array_T rows;
};


T UArray2_new(int width, int height, int size)
{
    assert(size>0);
    assert(width>0);
    assert(height>0);

    T uarray2;
    NEW(uarray2);
    //create the 'main' array (uarray->rows) whose dimensions are arbitrarily called width
    uarray2->rows = Array_new(width, sizeof(Array_T));

    //add an array of length 'height' at each iteration of the 'main' array
    for (int i=0; i<width; i++)
    {        
        Array_T* row_p = Array_get(uarray2->rows, i);
        *(row_p) = Array_new(height, size);
    }

    uarray2->size = size;
    uarray2->width = width;
    uarray2->height = height;    
    return uarray2;
}


void UArray2_free(T* uarray2)
{
    assert(uarray2);
    FREE((*uarray2)->rows); 
    FREE(*uarray2);    
}

int UArray2_width(T uarray2)
{
    assert(uarray2);
    return uarray2->width;
}

int UArray2_height(T uarray2)
{
    assert(uarray2);
    return uarray2->height;
}

int UArray2_size(T uarray2)
{
    assert(uarray2);
    return uarray2->size;
}

void* UArray2_at(T uarray2, int row, int col)
{
    assert(uarray2);
    assert(row<uarray2->width && col<uarray2->height);
    assert(row>=0 && col>=0);
    //return statement explained: cast Array_get(uarray2->rows at row#) to Array_T, dereference that,
    //then use Array_get again to get value at col#
    return Array_get(*((Array_T*)Array_get(uarray2->rows, row)), col);
}

//iterates through the UArray2 and apply function to each row
void UArray2_map_row_major(T uarray2, void Apply(void* row, void* cl), void* cl)
{
    assert(uarray2);
    for (int x=0; x<uarray2->width; x++)
    {
        Apply(Array_get(uarray2->rows, x), cl);
    }
}

//iterates through the UArray2 and apply function to each col
void UArray2_map_col_major(T uarray2, void Apply(void* col, void* cl), void* cl)
{
    assert(uarray2);
    for (int y=0; y<uarray2->height; y++)
    {
        Apply(Array_get(uarray2->rows, y), cl);
    }
}


