#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (!sign || !operand)
    {
      return -1;
    }

  *sign = value & 0x4000;

  *command = (value >> 7) & 0x7F;

  *operand = value & 0x7F;

  return 0;
}

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (!value)
    return -1;

  if (sign != 0 && sign != 1)
    {
      return -1;
    }

  if (command < 0 || command > 0x7F)
    {
      return -1;
    }

  if (operand < 0 || operand > 0x7F)
    {
      return -1;
    }

  int result = 0;

  result |= (sign << 14);

  result |= (command << 7);

  result |= operand;

  *value = result;
  return 0;
}

int
sc_commandValidate (int command)
{
  if (command >= 0x4000)
    {
      return -1;
    }

  return 0;
}

void
sc_printBinary (int number)
{

  for (int i = 14; i >= 0; i--)
    {
      printf ("%d", (number >> i) & 1);
    }

  printf ("\n");
}

int
sc_negative_to_dec (int num)
{

  num ^= 0x7fff;

  return num + 1;
}

void
sc_printDecodedCommand (int value)
{
  mt_gotoXY (20, 5);

  if (value & (1 << 14))
    printf ("DEC: -%d | ", sc_negative_to_dec (value));
  else
    printf ("DEC: %d | ", sc_negative_to_dec (value));

  printf ("OCT: %o | ", value);
  printf ("HEX: %x   bin: ", value);
  sc_printBinary (value);
}

void
sc_printCommand ()
{
  int value;
  int sign;
  int command;
  int operand;
  int row, col;

  mt_getscreensize (&row, &col);
  mt_gotoXY (7, col - 29);
  if (command_counter < SIZE && command_counter >= 0)
    {
      sc_memoryGet (command_counter, &value);
      sc_commandDecode (value, &sign, &command, &operand);

      if (sign)
        {
          printf ("- %x : %x", command, operand);
        }

      else
        {
          printf ("+ %x : %x", command, operand);
        }
    }

  else
    {
      if (sign)
        printf ("! + FF : FF");
      else
        printf ("! - FF : FF");
    }
}
