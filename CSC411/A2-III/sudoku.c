#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "array.h"
#include "pnmrdr.h"
#include "mem.h"
#include "assert.h"

/**
 * This function is the Apply for row and col major and takes the pointer to an Array_T
 * This is called once for each row or col array
 * i increments from the start to the end of the array
 * j increments from the i+1 to the end of the array for each i
 * if statement explained: cast array to Array_T, dereference that at array[i], cast that dereference to an int* then dereference to int
 * cl is a pointer to the isSolved variable
 * if i or j are ever equal then isSolved is changed to 1 (indicating the puzzle is not correct)
*/
void check_array(void* array, void* cl)
{
  for(int i=0; i<9; i++)
  {
    for(int j=i+1; j<9-i; j++)
    {
      if ( *((int*)(Array_get(*((Array_T*)array), i))) == *((int*)(Array_get(*((Array_T*)array), j))) )
      {
        *((int*)cl) = 1;
      }
    }
  }
}

FILE *fp;

int main(int argc, char **argv)
{ 
  //not stdin when argc>1
  if (argc > 2)
  {
    return EXIT_FAILURE;
  }
  //when the file name is given
  else if (argc == 2)
  {
    fp = fopen(argv[1], "r");
  }
  //when no file name is given (stdin)
  else if(argc == 1)
  {
    fp = stdin;
  }    
  if (fp == NULL)
  {
    return EXIT_FAILURE;
  }  
  
  //create reader and extract info
  Pnmrdr_T rdr = Pnmrdr_new(fp);
  Pnmrdr_T* rdr_p = &rdr;
  Pnmrdr_mapdata md = Pnmrdr_data(rdr);
  //ini the UArray2
  UArray2_T sudoku_puzzle = UArray2_new((int)md.width, (int)md.height, sizeof(int));
  UArray2_T* sudoku_puzzle_p = &sudoku_puzzle;
  //temp_p is used to copy elements to UArray2
  int* temp_p;
  //check if img is graymap, if so start copying sudoku puzzle
  assert(md.type == 2);
  for(int i=0; i<(int)md.width; i++)
  {
    for(int j=0; j<(int)md.height; j++)
    {
      temp_p = (int*)UArray2_at(sudoku_puzzle, i, j);
      *(temp_p) = (int)Pnmrdr_get(rdr);
    }
  }
  Pnmrdr_free(rdr_p);
  

  //When isSolved is 0 then exit(0) (puzzle is correct)
  //When isSolved is 1 then exit(1) (puzzle is not correct)
  int isSolved = 0;
  int* isSolved_p = &isSolved;
  UArray2_map_row_major(sudoku_puzzle, check_array, isSolved_p);
  UArray2_map_col_major(sudoku_puzzle, check_array, isSolved_p);
  fclose(fp);
  UArray2_free(sudoku_puzzle_p);

  if (isSolved == 0)
  {
    exit(0);
  }
  else
  {
    exit(1);    
  }

}