#include "../include/myBigChars.h"
#include "../include/myTerm.h"

void
sc_printInfo ()
{

  bc_box (22, 120, 7, 31, WHITE, BLACK, "INFO", GREEN, BLACK);

  mt_setbgcolor (BLACK);
  mt_setfgcolor (WHITE);

  mt_gotoXY (23, 121);

  printf ("l - load  s - save  i - reset");

  mt_gotoXY (24, 121);

  printf ("r - run  t - step");

  mt_gotoXY (25, 121);

  printf ("ESC - exit");

  mt_gotoXY (26, 121);

  printf ("F2 - accumulator");

  mt_gotoXY (27, 121);

  printf ("F4 - instruction counter");
}