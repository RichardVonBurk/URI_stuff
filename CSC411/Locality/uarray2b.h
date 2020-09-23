#ifndef UARRAY2B_INCLUDED
#define UARRAY2B_INCLUDED

#define T UArray2b_T
typedef struct T *T;

extern T UArray2b_new(int width, int height, int size, int blocksize);
extern T UArray2b_new_64K_block(int width, int height, int size);
extern void UArray2b_free(T* uarray2b);
extern int UArray2b_width(T uarray2b);
extern int UArray2b_height(T uarray2b);
extern int UArray2b_size(T uarray2b);
extern int UArray2b_blocksize(T uarray2b);
extern int UArray2b_num_blocks(T uarray2b);
extern void* UArray2b_at(T uarray2b, int row, int col);

extern void UArray2b_map(T uarray2b, void Apply(int row, int col, T uarray2b, void* elem, void* cl), void* cl);

#undef T
#endif