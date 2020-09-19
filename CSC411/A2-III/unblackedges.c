#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "array.h"
#include "pnmrdr.h"
#include "mem.h"
#include "assert.h"

/**
 * This function is recursive
 * it checks to see if a given bit is black (bit==1)
 * if it's black then it changes it to white (bit=0)
 * then check_bit gets called on all neighboring bits
 */
void check_bit(Bit2_T bit2, int row, int col)
{
  //check if current bit is black (bit==1)
  if (Bit2_get(bit2, row, col) == 1)
  {
    //change current bit
    Bit2_put(bit2, row, col, 0);

    //left side of page
    if (row == 0)
    {
      //top-left corner edge-case
      if (col == 0)
      {
        check_bit(bit2, row+1, col);
        check_bit(bit2, row, col+1);
      }
      //top-right corner edge-case
      else if (col == Bit2_height(bit2)-1)
      {
        check_bit(bit2, row+1, col);
        check_bit(bit2, row, col-1);
      }
      else
      {
        check_bit(bit2, row+1, col);
        check_bit(bit2, row, col+1);
        check_bit(bit2, row, col-1);
      }      
    }
    //right side of page
    else if (row == Bit2_width(bit2)-1)
    {
      //bottom-left corner edge-case
      if (col == 0)
      {
        check_bit(bit2, row-1, col);
        check_bit(bit2, row, col+1);
      }
      //bottom-right corner edge-case
      else if (col == Bit2_height(bit2)-1)
      {
        check_bit(bit2, row-1, col);
        check_bit(bit2, row, col-1);
      }
      else
      {
        check_bit(bit2, row-1, col);
        check_bit(bit2, row, col+1);
        check_bit(bit2, row, col-1);
      }
    }
    //top side of page
    else if(col == 0)
    {
      check_bit(bit2, row, col+1);
      check_bit(bit2, row+1, col);
      check_bit(bit2, row-1, col);
    }
    //bottom of page
    else if (col == Bit2_height(bit2)-1)
    {
      check_bit(bit2, row, col-1);
      check_bit(bit2, row+1, col);
      check_bit(bit2, row-1, col);
    }
  }  
}


/**
 * This function calls check_bit on all bits that are on the four edges of the bitmap 
 */
void unblackenedges(Bit2_T bit2)
{
  //check/change bits on top of page
  for(int j=0; j<Bit2_height(bit2); j++)
  {
    check_bit(bit2, 0, j);
  }
  //check/change bits on bottom of page
  for(int j=0; j<Bit2_height(bit2); j++)
  {
    check_bit(bit2, Bit2_width(bit2)-1, j);
  }
  //check/change bits on left of page
  for(int i=0; i<Bit2_width(bit2); i++)
  {
    check_bit(bit2, i, 0);
  }
  //check/change bits on left of page
  for(int i=0; i<Bit2_width(bit2); i++)
  {
    check_bit(bit2, i, Bit2_height(bit2)-1);
  }
}

//main
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
  Bit2_T bitfile = Bit2_new((int)md.width, (int)md.height);
  Bit2_T* bitfile_p = &bitfile;
  //temp_p is used to copy elements to UArray2
  int temp;
  //check if img is graymap, if so start copying sudoku puzzle
  for(int i=0; i<(int)md.width; i++)
  {
    for(int j=0; j<(int)md.height; j++)
    {
      temp = (int)Pnmrdr_get(rdr);
      Bit2_put(bitfile, i, j, temp);       
    }
  }
  Pnmrdr_free(rdr_p);
  fclose(fp);

  unblackenedges(bitfile);

  FILE* output_p = fopen("unblackened.pbm", "w");
  fputs("P4\n", output_p);
  int string_length;
  //check to see if length or width is a higher value
  if(Bit2_width(bitfile)>Bit2_height(bitfile))
  {
    string_length = Bit2_height(bitfile)+Bit2_height(bitfile)+1;
  }
  else
  {
    string_length = Bit2_width(bitfile)+Bit2_width(bitfile)+1;
  }

  //output steps
  char string[string_length];
  sprintf(string, "%d ", Bit2_width(bitfile));
  fputs(string, output_p);
  sprintf(string, "%d\n", Bit2_height(bitfile));
  fputs(string, output_p);

  for(int i=0; i<Bit2_height(bitfile); i++)
  {
    for(int j=0; j<Bit2_width(bitfile); j++)
    {
      sprintf(string, "%d", Bit2_get(bitfile, j, i));
      fputs(string, output_p);
      if(j!=Bit2_width(bitfile)-1)
      {
        sprintf(string, " ");
        fputs(string, output_p);
      }
      //move to next line
      else
      {
        sprintf(string, "\n");
        fputs(string, output_p);
      }      
    }
  }

  
  fclose(output_p);
  Bit2_free(bitfile_p);

}