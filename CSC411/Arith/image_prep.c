#include "pnm.h"
#include "assert.h"

void prep_img(Pnm_ppm img)
{
    assert(img);

    if (img->width%2 != 0)
    {
        img->width-=1;
    }
    
    if (img->height%2 != 0)
    {
        img->height-=1;
    }     
}