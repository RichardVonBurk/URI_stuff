#include "assert.h"
#include "pnm.h"

void rgb_to_ypp(int col, int row, A2 pixels, void *elem, void *cl)
{
        (void)pixels;
        CV value = malloc(sizeof(*value));

        const struct A2Methods_T *methods = ((Pnm_ppm)cl)->methods;
        Pnm_ppm img = (Pnm_ppm)cl;

        Pnm_rgb pixel = (Pnm_rgb)(methods->at(img->pixels, col, row));

        float r = (float)(pixel->red) / (float)(img->denominator);
        float g = (float)(pixel->green) / (float)(img->denominator);
        float b = (float)(pixel->blue) / (float)(img->denominator);
        
        float y = (0.299*r) + (0.587*g) + (0.114*b);
        float pb = (-0.168736*r) - (0.331264*g) + (0.5*b);
        float pr = (0.5*r) - (0.418688*g) - (0.081312*b);

        value->Y = y;
        value->Pb = pb;
        value->Pr = pr;
        
        *(CV)elem = (*value);
        free(value);
}