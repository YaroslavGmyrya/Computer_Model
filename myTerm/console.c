#include "../include/myTerm.h"
#include "../include/MySimpleComputer.h"

int
main ()
{
    fflush (stdout);
    struct winsize ws;

    if (!isatty (1))
        return -1;

    if (ioctl (1, TIOCGWINSZ, &ws) == -1)
    {
        if (ws.ws_row < MIN_H || ws.ws_col < MIN_W)
        {
            printf ("Window of terminal is small: %dx%d", ws.ws_row, ws.ws_col);
            return -1;
        }
    }

    fflush (stdout);

    mt_clrscr ();

    printf("%d", sc_memorySet(0, 16383));

    printf("%d", sc_memorySet(1, -1));

    for(int i = 0; i < SIZE; i++)
    {
        sc_printCell (i,WHITE,BLACK);
    }

    sc_printDecodedCommand (memory[1]);

    sc_printAccumulator ();

    sc_regSet(P, 1);

    sc_regSet(T, 1);

    sc_printFlags ();

    sc_printCounter ();

    sc_printCommand ();

    for(int i = 0; i < 7; i++)
    {
        int rand_value = rand () % 128;
        sc_addIOEntry (rand_value, '>', memory[i]);
    }

    sc_printTerm ();
   
    mt_setdefaultcolor ();
}