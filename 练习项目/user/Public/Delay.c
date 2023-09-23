#include "Delay.h"


void DelayMS(u8 msec)
{ 
    u8 i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}