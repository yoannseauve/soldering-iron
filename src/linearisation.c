#include <stdio.h>
#include <avr/pgmspace.h>
#include "linearisation.h"

unsigned char linearisation(float in)
{
    int first=0, last=255;
    int search;

    if (in > pgm_read_float(&(linearisationVals[255])))
        return 255;

    while ((last - first) > 1)
    {
        search = (last + first)/2;
        if ( in > pgm_read_float(&(linearisationVals[search])) )
            first = search;
        else
            last = search;
    }
    return ((unsigned char)(first));
}
