#include "../include/myTerm.h"
#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"
#include "../include/myReadKey.h"
#define ROWS 18                  
#define COLS 2

#define DEFAULT_FILE "font.bin"

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

    sc_memorySet(0, 16383);

    sc_TermUpdate(big_char);

    enum KEYS value;

    rk_mytermregime(1, 50, 1, 0, 1);
    //rk_mytermregime(0, 50, 1, 1, 1);

    while(1){
        rk_readkey(&value);
        if(value == KEYS_NAME[KEY_i] || value == KEYS_NAME[KEY_I]){
            sc_memorySet(0, 0);

            for (int i = 0; i < MAX_LINES; i++) {
                io_log[i].address = 0;
                io_log[i].type = 0;
                io_log[i].value = 0;
            }

            sc_TermUpdate(big_char);
        }

        else if(value == KEYS_NAME[KEY_RIGHT]){
            command_counter++;
            sc_TermUpdate(big_char);
        }

        else if(value == KEYS_NAME[KEY_LEFT]){
            command_counter--;
            sc_TermUpdate(big_char);
        }

        else if(value == KEYS_NAME[KEY_q])
            break;
    }

    rk_mytermregime(0, 50, 1, 1, 1);
}