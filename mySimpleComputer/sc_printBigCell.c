#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myBigChars.h"

void sc_printBigCell(int big_char[][2]){
    bc_box(10, 97, 11, 60, WHITE, BLACK, "BigCell", RED, BLACK);
    int value;
    int sign, command, operand;

    sc_memoryGet(command_counter, &value);
    sc_commandDecode(value, &sign, &command, &operand);

    int mask = 0xf;

    int result = 0;

    result |= command << 8;
    result |= operand;

    int tmp = 0;
    for(int i = 1; i <= 4; ++i){
        tmp = result & (mask << (4 * (i - 1)));
        tmp = tmp >> (4 * (i -1));
        bc_printbigchar(big_char[tmp], 11, 105 + ((5 - i) * 9), LIGHT_GREEN, BLACK);
    }

    if(sign)
        bc_printbigchar(big_char[16], 11, 105, LIGHT_GREEN, BLACK);
    else
        bc_printbigchar(big_char[17], 11, 105, LIGHT_GREEN, BLACK);
    fflush(stdout);
    return_table();
}