#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myBigChars.h"

int
sc_accumulatorGet (int *value) 
{ 
    if (!value) 
    { 
        return -1; 
    } 
 
    *value = accumulator; 
    return 0; 
} 

int
sc_accumulatorInit (void) 
{ 
    accumulator = 0; 
    return 0; 
} 

int
sc_accumulatorSet (int value) 
{ 
    if (value >= 0x800) 
    { 
        return -1; 
    } 
 
    accumulator = value; 
    return 0; 
} 

void
sc_printAccumulator (void) 
{ 
    struct winsize ws;

    ioctl (1, TIOCGWINSZ, &ws);

    bc_box(1,97,3,18, WHITE, BLACK, "Accumulator", RED, BLACK);

    mt_setfgcolor(WHITE);

    int value; 
    sc_accumulatorGet (&value);
    mt_gotoXY (2, 100); 
    printf ("sc: %d hex: %x\n", value, value); 
} 
