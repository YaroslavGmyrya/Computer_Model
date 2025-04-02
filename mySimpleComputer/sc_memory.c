#include "../include/MySimpleComputer.h"
#include "../include/myTerm.h"

int
sc_memoryGet (int address, int *value) 
{ 
    if (address >= SIZE || address < 0 || !value) 
    { 
        return -1; 
    } 
 
    *value = memory[address]; 
    return 0; 
} 

int
sc_memoryInit (void) 
{ 
    for (int i = 0; i < SIZE; i++) 
    { 
        memory[i] = 0; 
    } 
    return 0; 
} 

int
sc_memoryLoad (char *filename) 
{ 

    if (!filename)
      return -1;

    FILE *file = fopen (filename, "rb"); 
 
    if (!file) 
    { 
        return -1; 
    } 
 
    int result = fread (memory, sizeof(int), SIZE, file); 

    fclose (file); 
 
    if (result < SIZE) 
    { 
        return -1; 
    } 
 
    return 0; 
}

int
sc_memorySave (char *filename) 
{ 

    if (!filename)
        return -1;

    FILE *file = fopen (filename, "wb"); 
 
    if (!file) 
    { 
        return -1; 
    } 
 
    int result = fwrite (memory, sizeof(int), SIZE, file); 

    fclose (file); 
 
    if (result < SIZE) 
    { 
        return -1; 
    } 
 
    return 0; 
}


int
sc_memorySet (int address, int value) 
{ 
    if (address >= SIZE || value > 0x3fff || value < -0x3fff) 
    { 
        return -1; 
    } 

   
    if(value < 0){
        if(value != -16383)
            memory[address] = (abs(value) ^ 0x7fff) + 1;
        else
            memory[address] = (abs(value) ^ 0x7fff) + 1;
    }
    else
        memory[address] = value;
    return 0; 
} 

void
sc_printCell (int address, enum colors fg, enum colors bg) 
{ 

    int value;
    int sign;
    int command;
    int operand;
    int result = 0;

    sc_memoryGet (address,&value);
    sc_commandDecode (value, &sign, &command, &operand);

    result |= (command << 8);
    result |= operand;

    int row =  address / 10 + 2; 
    int col = (address % 10) * 7 + 3; 

    if (address >= 128 || address < 0) 
    { 
        return; 
    } 
    
    mt_gotoXY (row, col);

    if(address == 0){
        mt_setbgcolor(WHITE);
        mt_setfgcolor(BLACK);
    }

    else{
        mt_setfgcolor (fg);
        mt_setbgcolor (bg);
    }
       


    if(sign){
        if(value == 0)
            printf("%04x", 0);
        else
            printf ("-%02x", result);
        }
        
    else{
        if(value == 0)
            printf("+%04x", 0);
        else
            printf ("+%04x", result);
        }
        

}
