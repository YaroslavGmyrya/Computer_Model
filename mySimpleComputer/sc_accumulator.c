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
 
    if (value > 0x7fff || value < -0x7fff) 
    { 
        return -1; 
    } 

   
    if(value < 0){
        if(value != -16383)
            accumulator = (abs(value) ^ 0x7fff) + 1;
        else
            accumulator = (abs(value) ^ 0x7fff) + 1;
    }
    else
        accumulator = value;
    return 0; 
} 

void
sc_printAccumulator (void) 
{ 
    struct winsize ws;

    ioctl (1, TIOCGWINSZ, &ws);

    bc_box(1,96,3,22, WHITE, BLACK, "Accumulator", RED, BLACK);

    mt_setfgcolor(WHITE);

    int value, sign, command, operand; 

    sc_accumulatorGet (&value);

    sc_commandDecode(value, &sign, &command, &operand);

    mt_gotoXY (2, 97); 

    if(value & (1 << 14))
        printf ("sc: -%02x%02x hex: %04x\n", command, operand, value);
    else
        printf ("sc: +%02x%02x hex: %04x\n", command, operand, value);  
} 
