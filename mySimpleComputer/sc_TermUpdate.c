#include "../include/MySimpleComputer.h"
void sc_TermUpdate(int big_char[][2]){

    int counter_value = 0;
    int memory_value = 0;

    for(int i = 0; i < SIZE; i++)
    {   
        return_table();
        fflush(stdout);
        sc_printCell (i,WHITE,BLACK);
    }
    
    fflush(stdout);
    
    sc_icounterGet(&counter_value);

    sc_memoryGet(counter_value, &memory_value);

    sc_printDecodedCommand (memory_value);
    
    sc_printAccumulator ();
    
    sc_regSet(T, 1);
    
    sc_printFlags ();
    
    sc_printCounter ();
    
    fflush(stdout);
    return_table();
    
    sc_printCommand ();
    
    fflush(stdout);
    return_table();
    
    sc_printBigCell(big_char);
    
    fflush(stdout);
    
    
    sc_printTerm ();

    sc_printInfo();
    
    mt_gotoXY(35, 1);
    
    mt_setdefaultcolor ();
    
    fflush(stdout);
    return_table();
    fflush(stdout);
}