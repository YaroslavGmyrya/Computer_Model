#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../include/myTerm.h"

#define BIGCHAR_WIDTH 8
#define BIGCHAR_HEIGHT 8
#define ACS_CKBOARD 'a'

#define ROWS 17                  
#define COLS 2
#define DEFAULT_FILE "font.bin"

int switch_table(void);
int return_table(void);
int bc_strlen(char *str);
int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg, char *header, enum colors header_fg, enum colors header_bg);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_printbigchar(int *big, int x, int y, enum colors fg, enum colors bg);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);
