#include "../include/myTerm.h"
#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"

#define ROWS 18                  
#define COLS 2

#define DEFAULT_FILE "font"

int
main (int argc, char *argv[])
{
    const char *filename = (argc == 2) ? argv[1] : DEFAULT_FILE;

    int big_char[ROWS][COLS];

    FILE *file = fopen(filename, "rb");

    if (!file) {
        printf("Error in opening file\n");
        return 0;
    }

    int elements_read = fread(big_char, sizeof(int), ROWS * COLS, file);

    if (elements_read != ROWS * COLS) {
        printf("Warning: File read error, read only %d elements.\n", elements_read);
    }

    fclose(file);


    struct winsize ws;

    return_table();

    if (!isatty (1))
        return 0;

    if (ioctl (1, TIOCGWINSZ, &ws) == -1)
    {
        if (ws.ws_row < MIN_H && ws.ws_col < MIN_W)
        {
            printf ("Window of terminal is small: %dx%d", ws.ws_row, ws.ws_col);
            return 0;
        }
    }
    
    mt_clrscr ();

    printf("%d  %d", ws.ws_row, ws.ws_col);

    sc_memorySet(0, -16383);

    for(int i = 0; i < SIZE; i++)
    {   
        return_table();
        fflush(stdout);
        sc_printCell (i,WHITE,BLACK);
    }

    fflush(stdout);

    sc_printDecodedCommand (memory[0]);

    sc_printAccumulator ();

    sc_printFlags ();

    sc_printCounter ();

    fflush(stdout);
    return_table();

    sc_printCommand ();

    fflush(stdout);
    return_table();

    for(int i = 0; i < 7; i++)
    {
        sc_addIOEntry (i, '>', memory[i] < 0 ? memory[i] ^ (1 << 14) : memory[i]);
    }

    sc_printBigCell(big_char);

    fflush(stdout);

    //bc_printbigchar(big_char[0], 11, 98, LIGHT_GREEN, BLACK);
    //bc_printbigchar(big_char[1], 11, 107, LIGHT_GREEN, BLACK);
    //bc_printbigchar(big_char[2], 11, 115, LIGHT_GREEN, BLACK);
   // bc_printbigchar(big_char[3], 11, 124, LIGHT_GREEN, BLACK);
    //bc_printbigchar(big_char[5], 11, 133, LIGHT_GREEN, BLACK);


    sc_printTerm ();

    mt_gotoXY(35, 1);
   
    mt_setdefaultcolor ();

    fflush(stdout);
    return_table();
    fflush(stdout);
}