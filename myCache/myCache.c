#include "../include/myCache.h"
#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"
#include "../include/myTerm.h"

void
cahce_init ()
{

  srand (time (NULL));

  int index;

  int last_index[CACHE_ROWS] = { 0 };

  int index_exist;

  for (int i = 0; i < CACHE_ROWS;)
    {
      index_exist = 0;
      index = rand () % 12;

      for (int j = 0; j < CACHE_ROWS; ++j)
        {
          if (last_index[j] == index)
            {
              index_exist = 1;
              break;
            }
        }

      if (index_exist)
        continue;

      if (sc_get_line (index))
        {
          cache[i] = sc_get_line (index);
          last_index[i] = index;
          i++;
        }
    }
}

void
print_cache ()
{

  int sign, command, operand;

  bc_box (21, 1, 7, 72, WHITE, BLACK, "CACHE", GREEN, BLACK);

  mt_setfgcolor (WHITE);

  mt_gotoXY (22, 4);

  for (int i = 0; i < CACHE_ROWS; ++i)
    {
      for (int j = 0; j < CACHE_COLS; ++j)
        {

          sc_commandDecode (cache[i][j], &sign, &command, &operand);

          mt_gotoXY (22 + i, 4 + (j * 6));

          if (j == 0)
            {
              printf ("%d:", cache[i][j]);
            }

          else if (sign)
            {
              printf ("-%02x%02x", command, operand);
            }

          else
            {
              printf ("+%02x%02x", command, operand);
            }
        }
    }
}

int
value_in_cache (int address)
{
  for (int i = 0; i < CACHE_ROWS; ++i)
    {
      if (cache[i][0] == address - (address % 10))
        return 1;
    }

  return 0;
}

void
cache_update ()
{
  for (int i = 0; i < CACHE_ROWS; ++i)
    {
      int line = cache[i][0] / 10;

      cache[i] = sc_get_line (line);
    }
}