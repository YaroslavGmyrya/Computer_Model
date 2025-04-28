#include "../include/MySimpleComputer.h"

const int SIZE_COMMAND = 15;
int memory[SIZE];
int accumulator = 0;
int command_counter = 0;
int flags_register = 0;
int interputs_counter = 0;
int big_char[ROWS][COLS] = { { 0 } };
int processing = 0;