#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CACHE_COLS 11
#define CACHE_ROWS 5

extern int *cache[CACHE_ROWS];

void print_cache();
void cahce_init();
int value_in_cache(int address);
void cache_update();