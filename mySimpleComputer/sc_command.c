#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myBigChars.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand) 
{ 
    if (!sign || !operand) 
    { 
        return -1; 
    } 

    // Получаем знак (бит 14)
    *sign = (value >> 14) & 1;

    // Получаем команду (биты 13-7)
    *command = (value >> 7) & 0x7F; 

    // Получаем операнд (биты 6-0)
    *operand = value & 0x7F; 

    return 0; 
}

int
sc_commandEncode (int sign, int command, int operand, int *value) 
{
    if (!value) return -1;

    if (sign != 0 && sign != 1) { 
        return -1; 
    } 

    if (command < 0 || command > 0x7F) { // 7 бит на команду
        return -1; 
    } 

    if (operand < 0 || operand > 0x7F) { // 7 бит на операнд
        return -1; 
    } 

    int result = 0;

    // Устанавливаем знак (бит 14)
    result |= (sign << 14); 

    // Устанавливаем команду (биты 13-7)
    result |= (command << 7);

    // Устанавливаем операнд (биты 6-0)
    result |= operand;

    *value = result; 
    return 0; 
}

int
sc_commandValidate (int command) 
{ 
    if (command >= 0x800) 
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
        int bit = (number >> i) & 1; 
        printf ("%d", bit); 
    } 
    printf ("\n"); 
} 

int sc_negative_to_dec(int num){

    num ^= 0x7fff;

    return num + 1;
}

void
sc_printDecodedCommand (int value) 
{ 
    bc_box(17,1,3,72, WHITE, BLACK, "Editable cell (format)", RED, BLACK);

    mt_gotoXY (18, 10);
        
        if(value & (1 << 14))
            printf ("DEC: -%d | ", sc_negative_to_dec(value));
        else
            printf ("DEC: %d | ", sc_negative_to_dec(value));
    
        printf ("OCT: %o | ", value ^ (1 << 14)); 
        printf ("HEX: %x   bin: ", value ^ (1 << 14)); 
        sc_printBinary (value);  
}

void 
sc_printCommand ()
{
    fflush(stdout);
    return_table();

    bc_box(6,127,3,15, WHITE, BLACK, "Command", RED, BLACK);

    fflush(stdout);
    return_table();
    
    int value;
    int sign;
    int command;
    int operand;
    int row,col;

    mt_setfgcolor(WHITE);

    mt_getscreensize (&row, &col);
    mt_gotoXY (3, col - 20);
    if (command_counter < SIZE && command_counter >= 0)
    {
        sc_memoryGet (command_counter,&value);
        sc_commandDecode (value, &sign, &command, &operand);

        if (sign)
        {   
            fflush(stdout);
            return_table();
            printf ("- %x : %x", command, operand);
        }

        else
        {   
            fflush(stdout);
            return_table();
            printf ("+ %x : %x", command, operand);
        }
    }

    else
    {
        printf ("! + FF : FF");
    }
}
