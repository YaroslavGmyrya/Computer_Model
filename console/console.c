#include <stdio.h>
#include "../include/myBigChars.h"

int
main ()
{
  int big_char[][2] = {0xff000000,0xff};
  /*bc_setbigcharpos(big_char[0], 3, 0, 1);
  bc_setbigcharpos(big_char[0], 3, 1, 1);
  bc_setbigcharpos(big_char[0], 3, 2, 1);
  bc_setbigcharpos(big_char[0], 3, 3, 1);
  bc_setbigcharpos(big_char[0], 3, 4, 1);
  bc_setbigcharpos(big_char[0], 3, 5, 1);
  bc_setbigcharpos(big_char[0], 3, 6, 1);
  bc_setbigcharpos(big_char[0], 3, 7, 1);

  bc_setbigcharpos(big_char[0], 4, 0, 1);
  bc_setbigcharpos(big_char[0], 4, 1, 1);
  bc_setbigcharpos(big_char[0], 4, 2, 1);
  bc_setbigcharpos(big_char[0], 4, 3, 1);
  bc_setbigcharpos(big_char[0], 4, 4, 1);
  bc_setbigcharpos(big_char[0], 4, 5, 1);
  bc_setbigcharpos(big_char[0], 4, 6, 1);
  bc_setbigcharpos(big_char[0], 4, 7, 1);*/

  bc_printbigchar(big_char[0], 11, 90, GREEN, BLACK);

  printf("%x    %x\n\n", big_char[0][0], big_char[0][1]);

  //printf ("Hello World\n");
  return 0;
}
