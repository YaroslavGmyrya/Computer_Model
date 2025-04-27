#include "../include/MySimpleComputer.h"
#include "../include/myCache.h"
void sc_TermUpdate(){

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
    
    sc_printFlags ();
    
    sc_printCounter ();
    
    fflush(stdout);
    return_table();
    
    sc_printCommand ();
    
    fflush(stdout);
    return_table();
    
    sc_printBigCell();
    
    fflush(stdout);
    
    sc_printTerm ();

    sc_printInfo();

    cache_update();

    print_cache();
    
    mt_gotoXY(35, 1);
    
    mt_setdefaultcolor ();
    
    fflush(stdout);
    return_table();
    fflush(stdout);
}