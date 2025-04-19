#include "../include/myTerm.h"
#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"
#include "../include/myReadKey.h"

void
sc_addIOEntry (int address, char type, int value)
{    
    io_log[current_pos_log].address = address;
    io_log[current_pos_log].type = type;
    io_log[current_pos_log].value = value;

    current_pos_log++;

    if(current_pos_log > MAX_LINES)
        start++;
}

void 
sc_printTerm () 
{
    bc_box(22, 97, 9, 16, WHITE, BLACK, "IN-OUT", GREEN, BLACK);
    mt_gotoXY(26,100);
    mt_setfgcolor(WHITE);
    for (int i = start, j = 1; i < MAX_LINES + start - 1; i++) 
    {
        if (io_log[i].type != 0) 
        { 
            mt_gotoXY (22+j,100);
            if(io_log[i].value & (1<<14))
                printf("%03d %c -%04X\n", io_log[i].address, io_log[i].type, io_log[i].value);
            else
                printf("%03d %c +%04X\n", io_log[i].address, io_log[i].type, io_log[i].value);
            j++;
        }
    }
}