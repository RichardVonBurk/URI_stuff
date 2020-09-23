#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "uarray2b.h"
#include "array.h"
#include "arrayrep.h"
#include "assert.h"
#include "mem.h"

/**
 * This file is a two dimentional struc of an Array_T which at each iteration stores a struc Array_T
 * UArray2b elements are not defined and therefore UArray2b can be used with a lot data types
*/

#define T UArray2b_T

struct T
{
    int width;
    int height;
    int size;
    int blocksize;
    int num_blocks;
    Array_T rows;
};


T UArray2b_new(int width, int height, int size, int blocksize)
{
    assert(size>0);
    assert(width>0);
    assert(height>0);
    assert(blocksize>0);

    T uarray2b;
    NEW(uarray2b);
    //create the 'main' array (uarray->rows) whose dimensions are arbitrarily called width
    uarray2b->rows = Array_new(width, sizeof(Array_T));

    //add an array of length 'height' at each iteration of the 'main' array
    for (int i=0; i<width; i++)
    {        
        Array_T* row_p = Array_get(uarray2b->rows, i);
        *(row_p) = Array_new(height, size);
    }

    uarray2b->size = size;
    uarray2b->width = width;
    uarray2b->height = height;
    uarray2b->blocksize = blocksize;
    uarray2b->num_blocks = (ceil(uarray2b->height/uarray2b->blocksize) * ceil(uarray2b->width/uarray2b->blocksize));
    return uarray2b;
}

T UArray2b_new_64K_block(int width, int height, int size)
{
    assert(size>0);
    assert(width>0);
    assert(height>0);

    T uarray2b;
    NEW(uarray2b);
    //create the 'main' array (uarray->rows) whose dimensions are arbitrarily called width
    uarray2b->rows = Array_new(width, sizeof(Array_T));

    //add an array of length 'height' at each iteration of the 'main' array
    for (int i=0; i<width; i++)
    {        
        Array_T* row_p = Array_get(uarray2b->rows, i);
        *(row_p) = Array_new(height, size);
    }

    uarray2b->size = size;
    uarray2b->width = width;
    uarray2b->height = height;
    uarray2b->blocksize = ((int)floor(sqrt(65536)));
    uarray2b->num_blocks = (ceil(uarray2b->height/uarray2b->blocksize) * ceil(uarray2b->width/uarray2b->blocksize));    
    return uarray2b;
}


void UArray2b_free(T* uarray2b)
{
    assert(uarray2b);
    FREE((*uarray2b)->rows); 
    FREE(*uarray2b);    
}

int UArray2b_width(T uarray2b)
{
    assert(uarray2b);
    return uarray2b->width;
}

int UArray2b_height(T uarray2b)
{
    assert(uarray2b);
    return uarray2b->height;
}

int UArray2b_size(T uarray2b)
{
    assert(uarray2b);
    return uarray2b->size;
}

int UArray2b_blocksize(T uarray2b)
{
    assert(uarray2b);
    return uarray2b->blocksize;
}

int UArray2b_num_blocks(T uarray2b)
{
    assert(uarray2b);
    return uarray2b->num_blocks;
}

void* UArray2b_at(T uarray2b, int row, int col)
{
    assert(uarray2b);
    assert(row<uarray2b->width && col<uarray2b->height);
    assert(row>=0 && col>=0);
    //return statement explained: cast Array_get(uarray2b->rows at row#) to Array_T, dereference that,
    //then use Array_get again to get value at col#
    return Array_get(*((Array_T*)Array_get(uarray2b->rows, row)), col);
}

//iterates through the UArray2b and apply function to each block
void UArray2b_map(T uarray2b, void Apply(int row, int col, T uarray2b, void* elem, void* cl), void* cl)
{
    assert(uarray2b);
    for (int j=0; j<ceil(uarray2b->height/uarray2b->blocksize); j++)
    {
        for (int i=0; i<ceil(uarray2b->width/uarray2b->blocksize); i++)
        {
            for (int y=0; y<uarray2b->blocksize; y++)
            {
                for (int x=0; x<uarray2b->blocksize; x++)
                {
                    Apply( (i*uarray2b->blocksize)+x, (j*uarray2b->blocksize)+y, uarray2b, 
                        UArray2b_at(uarray2b, (i*uarray2b->blocksize)+x, (j*uarray2b->blocksize)+y), cl);
                }
            }            
        }        
    }
}



