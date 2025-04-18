#include <signal.h>
#include <sys/time.h>
#include "../include/MySimpleComputer.h"
#include "../include/myReadKey.h"

int ALU(int command, int operand) {
    int mem_value, accum_value;
    processing = 1;
    sc_memoryGet(operand, &mem_value);
    sc_accumulatorGet(&accum_value);

    switch (command) {
        case 0x1F: 
            interputs_counter = 10;

            sc_accumulatorSet(accum_value - mem_value); //0011111 0001010
            
            break;

        case 0x20:
            interputs_counter = 10;     //0100000 0001011

            if(mem_value == 0){
                sc_regSet(Z, 1);
                sc_accumulatorSet(0x7FFF); 
            }
                
            else
                sc_accumulatorSet(accum_value / mem_value); 

            break;

        case 0x2A:                          //00111110001101
            interputs_counter = 10;
            if(accum_value == 0)
                command_counter = operand;
            break;

        case 0x2B:                          //01010110000000
            interactive_mode = 1;
            processing = 0;
            sc_regSet(T, 1);
            break;
    }

    return 0;
}

void CU () {
    int sign, command, operand, instruction_counter, instruction;

    sc_icounterGet(&instruction_counter);

    if (sc_memoryGet(instruction_counter, &instruction) == 0 &&
        sc_commandDecode(instruction, &sign, &command, &operand) == 0 && interputs_counter == 0) {
            if (sc_commandValidate(command)){
                sc_addIOEntry(instruction_counter, '>', instruction);
                ALU(command, operand);
            }

            else{
                sc_addIOEntry(instruction_counter, '>', instruction);
                command_counter++;
            }
                
    }
}

void IRC(int signum) {
    if (signum == SIGALRM) {
        int flag_T;
        sc_regGet(T, &flag_T);

        if (flag_T && !force_step) return; 

        force_step = 0;

        if (interputs_counter > 0) {
            interputs_counter--;
            sc_TermUpdate();
            return;
        }

        if (processing && interputs_counter == 0) {
            command_counter++;
            processing = 0;
        }

        CU();
    }

    else if (signum == SIGUSR1) {
        command_counter = 0;
        accumulator = 0;
        sc_memoryInit();
        sc_regInit();
        sc_regSet(T, 1);
        interputs_counter = 0;
        interactive_mode = 1;
    }

    sc_TermUpdate();
}

void setup_timer() {
    signal(SIGALRM, IRC);  

    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000; 
    timer.it_value = timer.it_interval;

    setitimer(ITIMER_REAL, &timer, NULL); 
}
