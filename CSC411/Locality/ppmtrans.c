#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

//implementations for these functions are after main
void rotation_90(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl);
void rotation_180(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl);
void rotation_270(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl);

int main(int argc, char *argv[]) 
{
  FILE* img_file;
  int rotation = 0;

  A2Methods_T methods = array2_methods_blocked; // default to UArray2 methods
  assert(methods);
  A2Methods_mapfun *map = methods->map_default; // default to best map
  assert(map);

#define SET_METHODS(METHODS, MAP, WHAT) do { \
      methods = (METHODS); \
      assert(methods); \
      map = methods->MAP; \
      if (!map) { \
        fprintf(stderr, "%s does not support " WHAT "mapping\n", argv[0]); \
        exit(1); \
      } \
    } while(0)

  for (int i = 1; i < argc; i++) 
  {
    if (!strcmp(argv[i], "-row-major")) {
      SET_METHODS(array2_methods_plain, map_row_major, "row-major");
    } else if (!strcmp(argv[i], "-col-major")) {
      SET_METHODS(array2_methods_plain, map_col_major, "column-major");
    } else if (!strcmp(argv[i], "-block-major")) {
      SET_METHODS(array2_methods_blocked, map_block_major, "block-major");
    } else if (!strcmp(argv[i], "-rotate")) {
      assert(i + 1 < argc);
      char *endptr;
      rotation = strtol(argv[++i], &endptr, 10);
      assert(*endptr == '\0'); // parsed all correctly
      assert(rotation == 0   || rotation == 90
          || rotation == 180 || rotation == 270);
    } else if (*argv[i] == '-') {
      fprintf(stderr, "%s: unknown option '%s'\n", argv[0], argv[i]);
      exit(1);
    } else if (argc - i > 2) {
      fprintf(stderr, "Usage: %s [-rotate <angle>] "
              "[-{row,col,block}-major] [filename]\n", argv[0]);
      exit(1);
    } else {
      break;
    }
  }

  //Check for proper input and check if stdin

  for (int i = 1; i < argc; i++)
  {
    img_file = fopen(argv[i], "w");
    if (img_file == NULL)
    {
	    exit(1);
    }
    else
    {
	    img_file = stdin;
      assert(img_file != NULL);
    }
  }

  //after file/stdin extract the img
  Pnm_ppm initial_img = Pnm_ppmread(img_file, methods);
  //our 'output' img
  Pnm_ppm rotated_img = (Pnm_ppm)malloc(sizeof(*(initial_img)));
  rotated_img->denominator = initial_img->denominator;
  rotated_img->methods = initial_img->methods;

  //90 and 270 both swap height and width at first
  if (rotation==90 || rotation==270)
  {
    rotated_img->width = initial_img->height;
		rotated_img->height = initial_img->width;    
    rotated_img->pixels = methods->new(initial_img->height, initial_img->width, sizeof(Pnm_rgb));
    //90 degree rotation
    if (rotation==90)
    {
      map(initial_img->pixels, rotation_90, rotated_img);
    }
    //270 degree rotation
    else
    {
      map(initial_img->pixels, rotation_270, rotated_img);
    }
    Pnm_ppmwrite(stdout, rotated_img);
    Pnm_ppmfree(&initial_img);
    Pnm_ppmfree(&rotated_img);   
  }
  //180 keeps same dimensions as original
  else if (rotation==180)
  {
    rotated_img->width = initial_img->width;
		rotated_img->height = initial_img->height;
    rotated_img->pixels = methods->new(initial_img->width, initial_img->height, sizeof(struct Pnm_rgb));	
		map(initial_img->pixels, rotation_180, rotated_img); //rotation is called
    Pnm_ppmwrite(stdout, rotated_img);
    Pnm_ppmfree(&initial_img);
    Pnm_ppmfree(&rotated_img);
  }
  //no rotation needed for 0 degrees
  else if (rotation==0)
  {
    Pnm_ppmwrite(stdout, initial_img);
  }

  fclose(img_file);     
  
  
}

//rotation functions

void rotation_90(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl)
{
  (void)input_img;
  Pnm_rgb input_pixel = (Pnm_rgb)elem;
  Pnm_ppm output_image = (Pnm_ppm)cl;
  Pnm_rgb output_pixel = (Pnm_rgb)(output_image->methods->at(output_image->pixels, (output_image->width-j-1), i));
	*(output_pixel) = *(input_pixel);
}

void rotation_180(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl)
{
  (void)input_img;
  Pnm_rgb input_pixel = (Pnm_rgb)elem;
  Pnm_ppm output_image = (Pnm_ppm)cl;
  Pnm_rgb output_pixel = (Pnm_rgb)(output_image->methods->at(output_image->pixels, (output_image->width-i-1), (output_image->height-j-1)));
	*(output_pixel) = *(input_pixel);
}

void rotation_270(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl)
{
  (void)input_img;
  Pnm_rgb input_pixel = (Pnm_rgb)elem;
  Pnm_ppm output_image = (Pnm_ppm)cl;
  Pnm_rgb output_pixel = (Pnm_rgb)(output_image->methods->at(output_image->pixels, j, (output_image->width-i-1)));
	*(output_pixel) = *(input_pixel);
}


void flip_horizontal(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl)
{
  (void)input_img;
  Pnm_rgb input_pixel = (Pnm_rgb)elem;
  Pnm_ppm output_image = (Pnm_ppm)cl;
  Pnm_rgb output_pixel = (Pnm_rgb)(output_image->methods->at(output_image->pixels, (output_image->width-i-1), j));
	*(output_pixel) = *(input_pixel);
}
//void flip_vertical(int i, int j, A2Methods_Array2 input_img, void* elem, void* cl)