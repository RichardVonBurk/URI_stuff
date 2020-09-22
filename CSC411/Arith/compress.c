#include "compress.h"
#include "pnm.h"
#include "a2blocked.h"
#include "a2methods.h"
#include "image_prep.h"
#include "image_trans.h"

void compress(FILE *input, A2Methods_T methods)
{
    Pnm_ppm img = read_image(FILE *input, methods);
    prep_img(img);
}


void decompress(FILE *input)
{
    
}