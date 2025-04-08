#include <stdio.h>
#define ROWS 18
#define COLS 2

int main(){

    int big_char[][2] = {
        {0x24242418, 0x18242424},   //0
        {0x10101018, 0x38101010},   //1
        {0x020202018,0x34040438},   //2
        {0x20202038, 0x38202020},   //.....
        {0x3C242424, 0x20202020},
        {0x38080838, 0x3C202038},
        {0x404043C, 0x3C24243C},
        {0x1010101C, 0x10103810},
        {0x3C24243C, 0x3C24243C},
        {0x3C24243C, 0x3C24243C},
        {0x3C24243C ,0x24242424},   // A
        {0x3C24243C,  0x3C243C04},  // B
        {0x4040870 , 0x70080404},   // ...
        {0x2424140C,  0xC142424},
        {0x3C04043C,  0x1C04043C},
        {0x404043C,  0x404043C},
        {0xff000000,0xff},          //-
        {0x7C180000,  0x187C},      // +
    };

    FILE *file = fopen("../font.bin", "wb");

    fwrite(big_char, sizeof(int), ROWS * COLS, file);

    fclose(file);

    return 0;
}