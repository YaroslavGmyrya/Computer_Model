#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"
#include "../include/myTerm.h"

int
sc_icounterGet (int *value)
{
  if (!value)
    {
      return -1;
    }

  *value = command_counter;
  return 0;
}

int
sc_icounterInit (void)
{
  command_counter = 0;
  return 0;
}

int
sc_icounterSet (int value)
{
  if (value < 0 || value > 127)
    {
      sc_regSet (M, 1);
      return -1;
    }

  command_counter = value;
  return 0;
}

void
sc_printCounter (void)
{
  struct winsize ws;

  ioctl (1, TIOCGWINSZ, &ws);

  bc_box (6, 96, 3, 22, WHITE, BLACK, "Counter", RED, BLACK);

  int value;
  int row, col;

  mt_getscreensize (&row, &col);
  sc_icounterGet (&value);

  mt_setfgcolor (WHITE);

  mt_gotoXY (7, col - 61);

  printf ("T: %03d     IC: %03x", interputs_counter, value);
}