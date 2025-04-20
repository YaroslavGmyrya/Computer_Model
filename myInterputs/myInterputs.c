#include <signal.h>
#include <sys/time.h>
#include "../include/MySimpleComputer.h"
#include "../include/myReadKey.h"
#include "../include/myInterputs.h"

int halt_flag = 0;

void IRC(int signum);

int ALU(int command, int operand) {
    int mem_value, accum_value, val;
    processing = 1;
    sc_memoryGet(operand, &mem_value);
    sc_accumulatorGet(&accum_value);

    switch (command) {

        //SUB
        case 0x1F: 
            interputs_counter = 10;

            sc_accumulatorSet(accum_value - mem_value);
            
            break;

        //DIVIDE 
        case 0x20:
            interputs_counter = 10;     

            if(mem_value == 0){
                sc_regSet(Z, 1);
                sc_accumulatorSet(0x7FFF); 
            }
                
            else
                sc_accumulatorSet(accum_value / mem_value); 

            break;

        //JZ
        case 0x2A:                          
            interputs_counter = 2;
            if(accum_value == 0)
                sc_icounterSet(operand - 1);
            break;

        //HALT
        case 0x2B:  
            halt_flag = 1;
            break;

        //extra command
        
        //LOAD
        case 0x14:
            interputs_counter = 10;
            sc_accumulatorSet(memory[operand]);
            break;
        
        //JNS
        case 0x37:
            interputs_counter = 2;
            sc_accumulatorGet(&val);

            if(val > 0)
                sc_icounterSet(operand);

            break;

        //MUL
        case 0x21:
            interputs_counter = 2;
            sc_accumulatorGet(&val);
            sc_accumulatorSet(val * memory[operand]);
            break;

        //STORE
        case 0x15:
            interputs_counter = 10;
            memory[operand] = accumulator;   
            break;   
        
        //JUMP
        case 0x28:
            interputs_counter = 2;
            sc_icounterSet(operand);
            break;

        //READ
        case 0x0A:
            interputs_counter = 10;
            char ch;
            char buffer[6] = {'\0'};
            int i = 0;
            int res;
            int x = 25, y = 30;

            mt_gotoXY(y,x);
            printf("Введите значение, которое Вы хотите записать по адресу %d: ", operand);
            mt_gotoXY(++y,x);
            while(1){
                rk_readkey(&ch);

                if(ch == KEYS_NAME[KEY_ESC])
                    break;

                if(ch >= KEYS_NAME[KEY_0] && ch <= KEYS_NAME[KEY_9]){
                    rk_mytermregime(1, 50, 1, 1, 1);
                    buffer[i++] = ch;
                    printf("%c", ch);
                    mt_gotoXY(y, ++x);
                }

                if(ch == KEYS_NAME[KEY_BACKSPACE]){
                    rk_mytermregime(1, 50, 1, 1, 1);
                    buffer[--i] = '\0';
                    printf(" ");
                    
                    mt_gotoXY(y, --x);
                }

                if(ch == KEYS_NAME[KEY_ENTER]){
                    res = rk_string_dec_to_dec(buffer);
                    memory[operand] = res;
                    printf("\n%d", res);
                    break;
                }

                
            }

            rk_mytermregime(1, 50, 1, 0, 1);

            break;
    }

    return 0;
}

//A14 записать n в аккумулятор из 20 ячейки
//1507 если n == 0, то переход на останов (7 ячейка)
//1580 - останов (7 ячейка)
//A16 - загружаем текущее значение fact (22 ячйека)
//1094 умножить аккумулятор на значние n в памяти (20 ячейка)
//A96 Записать значение из аккамулятора в память (22 ячейка)
//A14 Загрузить n в аккум (из 20 ячейки)
//F95 Декрементировать n с помощью единицы, записанной в ячейке 21
//A94 Сохранить новое значение в память (20 ячейка)
//1400 Переход на нулевую ячейку

void CU () {
    int sign, command, operand, instruction_counter, instruction;

    sc_icounterGet(&instruction_counter);

    if (sc_memoryGet(instruction_counter, &instruction) == 0 &&
        sc_commandDecode(instruction, &sign, &command, &operand) == 0 && interputs_counter == 0) {
            if (sc_commandValidate(command)){
                //sc_addIOEntry(instruction_counter, '>', instruction);
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

        if (halt_flag) {
            command_counter = 0;
            accumulator = 0;
            sc_regInit();            
            sc_regSet(T, 1);         
            interputs_counter = 0;
            interactive_mode = 1;
            force_step = 0;
            sc_TermUpdate();
            return;                  
        }

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
