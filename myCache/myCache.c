#include "../include/myCache.h"
#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myBigChars.h"

int cahce_init(){

    srand(time(0));

    int index;

    int last_index[CACHE_ROWS] = {0};

    int index_exist;

    for(int i = 0; i < CACHE_ROWS;){
        index_exist = 0;
        index = rand() % 12;

        for(int j = 0; j < CACHE_ROWS; ++j){
            if(last_index[j] == index){
                index_exist = 1;
                break;
            }
        }

        if(index_exist)
            continue;

        if(sc_get_line(index)){
            cache[i] = sc_get_line(index);
            last_index[i] = index;
            i++;
        }
            
    }
}

void print_cache(){

    bc_box(21, 1, 7, 72, WHITE, BLACK, "CACHE", GREEN, BLACK);

    mt_setfgcolor(WHITE);

    mt_gotoXY(22, 4);

    for(int i = 0; i < CACHE_ROWS; ++i){
        for(int j = 0; j < CACHE_COLS; ++j){
            
            mt_gotoXY(22 + i, 4 + (j * 6));

            if(j == 0){
                printf("%d:", cache[i][j]);
            }

            else if(cache[i][j] & (1 << 14)){
                printf("-%04x", cache[i][j]);
            }

            else{
                printf("+%04x", cache[i][j]);
            }
                
        }
    }
}

int value_in_cache(int address){
    for(int i = 0; i < CACHE_ROWS; ++i){
        if(cache[i][0] == address - (address % 10))
            return 1;
    }

    return 0;
}
