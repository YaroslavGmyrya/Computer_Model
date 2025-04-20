#include "../include/myTerm.h"
#include "../include/MySimpleComputer.h"
#include "../include/myBigChars.h"
#include "../include/myReadKey.h"
#include "../include/myInterputs.h"
#include <signal.h>
#include <sys/time.h>

int
main (int argc, char *argv[])
{
    const char *filename = (argc == 2) ? argv[1] : DEFAULT_FILE;

    FILE *file = fopen(filename, "rb");

    if (!file) {
        printf("Error in opening file\n");
        return 0;
    }

    int elements_read = fread((void *)big_char, sizeof(int), ROWS * COLS, file);

    if (elements_read != ROWS * COLS) {
        printf("Warning: File read error, read only %d elements.\n", elements_read);
    }

    fclose(file);

    struct winsize ws;

    return_table();

    if (!isatty (1))
        return 0;

    if (ioctl (1, TIOCGWINSZ, &ws) == -1)
    {
        if (ws.ws_row < MIN_H && ws.ws_col < MIN_W)
        {
            printf ("Window of terminal is small: %dx%d", ws.ws_row, ws.ws_col);
            return 0;
        }
    }
    
    mt_clrscr ();

    sc_memorySet(0, 16383);

    sc_regSet(T, 1);

    for(int i = 0; i < 7; i++)
    {
        sc_addIOEntry (i, '<', memory[i] < 0 ? memory[i] ^ (1 << 14) : memory[i]);
    }

    sc_TermUpdate();

    enum KEYS value;

    rk_mytermregime(1, 50, 1, 0, 1);

    while(1){

        rk_readkey(&value);

        rk_mytermregime(1, 50, 1, 0, 1);
        
        if(value == KEYS_NAME[KEY_ESC]){
            sc_TermUpdate();
            break;
        }

        else if((value == KEYS_NAME[KEY_T] || value == KEYS_NAME[KEY_t]) && interactive_mode){
            force_step = 1;
            signal(SIGALRM, IRC);
            raise(SIGALRM);
        }

        else if((value == KEYS_NAME[KEY_o] || value == KEYS_NAME[KEY_O]) && interactive_mode){
            int y = 23, x = 100;

            int min_y, min_x, max_y, max_x;

            max_y = 30, max_x = 110, min_y = 23, min_x = 100;

            int block = 0;

            char type = '\0';
            char address[4] = {'\0'};
            char val[6] = {'\0'};

            int address_i = 0;
            int val_i = 0;

            while(1){
                rk_readkey(&value);
                mt_gotoXY(y, x);
                if(value == KEYS_NAME[KEY_ESC]){
                    sc_TermUpdate();
                    break;
                }

                else if(value == KEYS_NAME[KEY_BOTTOM]){
                    if(y + 1 < max_y)
                        mt_gotoXY(++y, x);
                    else{
                        start++;
                        printf("%d", start);
                    }
                }

                else if(value == KEYS_NAME[KEY_TOP]){
                    if(y - 1 >= min_y)
                        mt_gotoXY(--y, x);
                }

                else if(value == KEYS_NAME[KEY_RIGHT]){
                    if(x + 1 <= max_x){
                        if(x + 1 == 103 || x + 1 == 105){
                            block += 1;
                            x += 2;
                            mt_gotoXY(y, x);
                        }

                        else{
                            mt_gotoXY(y, ++x);
                        }
                    }
                }

                else if(value == KEYS_NAME[KEY_LEFT]){
                    if(x - 1 >= min_x)
                        if(x - 1 == 103 || x - 1 == 105){
                            block -= 1;
                            x -= 2;
                            mt_gotoXY(y, x);
                        }
                        else{
                            mt_gotoXY(y, --x);
                        } 
                }

                else if(value == KEYS_NAME[KEY_ENTER]){
                    while(1){
                        mt_gotoXY(y, x);
                        rk_readkey(&value);
                        if(value == KEYS_NAME[KEY_ESC]){
                            sc_TermUpdate();
                            break;
                        }

                        else if (value == KEYS_NAME[KEY_BACKSPACE]) {
                            if(x - 1 >= min_x){
                                printf(" ");

                                if(x - 1 == 103 || x - 1 == 105)
                                    block -= 1;

                                if(block == 0){
                                    address[x - min_x] = ' ';
                                }
    
                                if(block == 1){
                                    type = ' ';
                                }
    
                                if(block == 2){
                                    val[x - min_x - 6] = ' ';
                                }

                                if(x - 1 == 103 || x - 1 == 105){
                                    x -= 2;
                                    mt_gotoXY(y, x);
                                }
                                else{
                                    mt_gotoXY(y, --x);
                                } 
                            }

                            mt_gotoXY(30, 40);
                            printf("%s\n%d", address, block);
                        }

                        else if ((KEYS_NAME[KEY_a] <= value && value <= KEYS_NAME[KEY_f]) ||
                        (KEYS_NAME[KEY_A] <= value && value <= KEYS_NAME[KEY_F]) ||
                        value == KEYS_NAME[KEY_PLUS] || value == KEYS_NAME[KEY_MINUS] ||
                        (KEYS_NAME[KEY_0] <= value && value <= KEYS_NAME[KEY_9]) || 
                        value == KEYS_NAME[KEY_MORE] || value == KEYS_NAME[KEY_LESS]) {
        
                            if (block == 0 &&
                                value != KEYS_NAME[KEY_PLUS] &&
                                value != KEYS_NAME[KEY_MINUS] &&
                                value != KEYS_NAME[KEY_MORE] &&
                                value != KEYS_NAME[KEY_LESS]) {
                                address[x - min_x] = value;
                                printf("%c", value);
                            }

                            else if (block == 1 && (value == KEYS_NAME[KEY_MORE] || value == KEYS_NAME[KEY_LESS])) {
                                type = value;
                                printf("%c", value);
                            }

                            else if(block == 2 && (value != KEYS_NAME[KEY_MORE] || value != KEYS_NAME[KEY_LESS])){
                                val[x - min_x - 6] = value;
                                printf("%c", value);
                            }

                            if(x + 1 == 103 || x + 1 == 105){
                                x += 2;
                                block += 1;
                                if(block == 0)
                                    printf("%c", value);

                                mt_gotoXY(y, x);
                            }
    
                            else if(x < max_x){
                               mt_gotoXY(y, ++x);
                            }


                            mt_gotoXY(30, 40);
                            printf("%s\n%d\n", address, block);
                            printf("%c\n%d\n", type, block);
                            printf("%s\n%d\n", val, block);
                        }

                        else if(value == KEYS_NAME[KEY_ENTER]){
                            int num_address = rk_string_dec_to_dec(address);
                            char unsigned_val[5];
                            strcpy(unsigned_val, val + 1);
                            mt_gotoXY(32, 40);
                            int num_val = rk_hex_to_dec(unsigned_val);

                            if(val[0] == '-')
                                num_val = - num_val;

                            if(type == '<'){
                                sc_addIOEntry(num_address, type, num_val);
                                memory[num_address] = num_val;
                            }

                            if(type == '>'){
                                int mem_val = memory[num_address];

                                if(mem_val == num_val){
                                    sc_accumulatorSet(mem_val);
                                    sc_addIOEntry(num_address, type, mem_val);
                                }  
                            }

                            sc_TermUpdate();
                           
                        }
                    }
                }
            }
        }
            
        else if((value == KEYS_NAME[KEY_R] || value == KEYS_NAME[KEY_r]) && interactive_mode){
            interactive_mode = 0;
            sc_regSet(T, 0);
            rk_readkey(&value);
            setup_timer();
            while(1){
                rk_readkey(&value);
               
                if(value == KEYS_NAME[KEY_ESC]){
                    interactive_mode = 1;
                    break;
                }
            }
        }


        else if(value == KEYS_NAME[KEY_i] || value == KEYS_NAME[KEY_I] && interactive_mode){

            sc_memoryInit();

            sc_accumulatorSet(0);

            sc_regSet(M, 0);

            sc_regSet(E, 0);

            sc_regSet(P, 0);

            sc_regSet(Z, 0);

            for (int i = 0; i < MAX_LINES; i++) {
                io_log[i].address = 0;
                io_log[i].type = 0;
                io_log[i].value = 0;
            }

            sc_TermUpdate();
        }

        else if(value == KEYS_NAME[KEY_RIGHT] && interactive_mode){

            if(command_counter + 1 > 127)
                command_counter = 0;
            
            else
                command_counter++;

            sc_TermUpdate();
        }

        else if(value == KEYS_NAME[KEY_LEFT] && interactive_mode){

            if(command_counter - 1 < 0)
                command_counter = 127;
        
            else
                command_counter--;

            sc_TermUpdate();
        }

        else if(value == KEYS_NAME[KEY_TOP] && interactive_mode){

            if(command_counter - 10 < 0)
                command_counter = 120 + (command_counter % 10);
        
            else
                command_counter -= 10;

            sc_TermUpdate();
        }

        else if(value == KEYS_NAME[KEY_BOTTOM] && interactive_mode){

            if(command_counter + 10 > 127)
                command_counter = 0 + (command_counter % 10);

            else
                command_counter+=10;

            sc_TermUpdate();
        }

        else if(value == KEYS_NAME[KEY_S] || value == KEYS_NAME[KEY_s] && interactive_mode){
            mt_gotoXY(26, 40);
            rk_mytermregime(1, 50, 1, 1, 1);
            int i = 0;
            char buffer[200];

            while(value != KEYS_NAME[KEY_ENTER]){
                rk_readkey(&value);

                buffer[i++] = value;
            }

            buffer[i] = '\0';

            sc_memorySave(buffer);
            
           
        }

        else if(value == KEYS_NAME[KEY_L] || value == KEYS_NAME[KEY_l] && interactive_mode){
            int  x = 26, y = 40;
            mt_gotoXY(x, y);
            rk_mytermregime(1, 50, 1, 1, 1);
            int i = 0;
            char buffer[200] = {'\0'};

            while(value != KEYS_NAME[KEY_ENTER]){

                if (value == KEYS_NAME[KEY_ESC]) {
                    sc_TermUpdate();
                    break;
                }

                else if (value == KEYS_NAME[KEY_BACKSPACE]) {
                        buffer[--i] = '\0';
                        printf(" ");
                        
                        y--;
                        mt_gotoXY(x, y);
                    }

                rk_readkey(&value);

                buffer[i++] = value;
            }

            sc_memoryLoad(buffer);
            sc_TermUpdate();
         }

       else if (value == KEYS_NAME[KEY_F2] && interactive_mode) {
    int x = 2, y = 116;
    int block = 0;
    int y_max = y;
    int y_min = y - 5;

    mt_gotoXY(x, y);
    rk_readkey(&value);

    char buffer[6];
    buffer[5] = '\0';
    rk_accumulator_to_string(buffer);
    int current_pos = 6;

    while (1) {
        mt_gotoXY(x, y);
        rk_mytermregime(1, 50, 1, 0, 1);
        rk_readkey(&value);

        if (value == KEYS_NAME[KEY_BACKSPACE]) {
            if (current_pos > 0) {
                buffer[--current_pos] = ' ';
                if (y > y_min)
                    y--;
                printf(" ");
                mt_gotoXY(x, y);
            }
        }

        else if (value == KEYS_NAME[KEY_RIGHT]) {
            if (y < y_max) {
                current_pos++;
                y++;
                mt_gotoXY(x, y);
            }
            else if (y >= y_max && block) {
                block--;
                y += 7;
                y_min = y - 1;
                y_max = y + 4;

                mt_gotoXY(x, y);
                rk_accumulator_to_string(buffer);
                current_pos = 5;
            }
        }

        else if (value == KEYS_NAME[KEY_LEFT]) {
            if (y > y_min + 1) {
                current_pos--;
                y--;
                mt_gotoXY(x, y);
            }
            else if (y <= y_min + 1 && !block) {
                block++;
                y -= 7;
                y_max = y;
                y_min = y - 5;

                mt_gotoXY(x, y);
                rk_accumulator_to_string(buffer);
                current_pos = 5;
            }
        }

        else if ((KEYS_NAME[KEY_a] <= value && value <= KEYS_NAME[KEY_f]) ||
                 (KEYS_NAME[KEY_A] <= value && value <= KEYS_NAME[KEY_F]) ||
                 value == KEYS_NAME[KEY_PLUS] || value == KEYS_NAME[KEY_MINUS] ||
                 (KEYS_NAME[KEY_0] <= value && value <= KEYS_NAME[KEY_9])) {

            if (y < y_max)
                y++;

            if (current_pos < 5) {
                buffer[current_pos++] = value;
                rk_mytermregime(1, 50, 1, 1, 1);
                mt_gotoXY(x, y);
                printf("%c", value);
            }
        }

        else if (value == KEYS_NAME[KEY_ENTER]) {
            if (block == 0) {

                char unsigned_buffer[5]; 
                strncpy(unsigned_buffer, buffer + 1, 4);
                mt_gotoXY(33, 40);
                printf("%s", unsigned_buffer);
                int val = rk_hex_to_dec(unsigned_buffer);
                printf("%d", val);
                sc_accumulatorSet(val);
                sc_TermUpdate();
            } else {
                char operand_char[3] = {'\0'};
                char command_char[3] = {'\0'};

                command_char[0] = buffer[1];
                command_char[1] = buffer[2];
                operand_char[0] = buffer[3];
                operand_char[1] = buffer[4];
                int command_int = rk_hex_to_dec(command_char);
                int operand_int = rk_hex_to_dec(operand_char);
                int encoded_value;

                if (buffer[0] == '+')
                    sc_commandEncode(0, command_int, operand_int, &encoded_value);
                else if (buffer[0] == '-')
                {
                    sc_commandEncode(1, command_int, operand_int, &encoded_value);
                }
                    

                mt_gotoXY(40, 40);
                printf("%x", encoded_value);
                sc_accumulatorSet(encoded_value);
                sc_TermUpdate();
            }
            break;
        }

        else if (value == KEYS_NAME[KEY_ESC]) {
            sc_TermUpdate();
            break;
        }
    }
}

    else if (value == KEYS_NAME[KEY_F4] && interactive_mode) {
        int x = 7, y = 116;
        int block = 0;
        int y_max = y - 1;
        int y_min = y - 3;

        mt_gotoXY(x, y);
        rk_readkey(&value);

        char buffer[4] = {'\0'};
        rk_counter_to_string(buffer);
        int current_pos = 3;

        while (1) {
            mt_gotoXY(x, y);
            rk_mytermregime(1, 50, 1, 0, 1);
            rk_readkey(&value);

            if (value == KEYS_NAME[KEY_BACKSPACE]) {
                if (current_pos > 0) {
                    current_pos--;
                    buffer[current_pos] = ' ';
                    if (y - 1 >= y_min) y--;
                    mt_gotoXY(x, y);
                    printf(" ");
                }
                mt_gotoXY(30, 30);
                printf("%s", buffer);
            }

            else if (value == KEYS_NAME[KEY_RIGHT]) {
                if (y + 1 <= y_max) {
                    current_pos++;
                    y++;
                    mt_gotoXY(x, y);
                } else if (block) {
                    block--;
                    y += 10;
                    y_min = y - 1;
                    y_max = y + 2;
                    mt_gotoXY(x, y);
                    rk_counter_to_string(buffer);
                    current_pos = 3;
                }
            }

            else if (value == KEYS_NAME[KEY_LEFT]) {
                if (y - 1 > y_min) {
                    current_pos--;
                    y--;
                    mt_gotoXY(x, y);
                } else if (!block) {
                    block++;
                    y -= 10;
                    y_max = y;
                    y_min = y - 4;
                    mt_gotoXY(x, y);
                    rk_counter_to_string(buffer);
                    current_pos = 3;
                }
            }

            else if ((KEYS_NAME[KEY_0] <= value && value <= KEYS_NAME[KEY_9]) || 
                    (KEYS_NAME[KEY_A] <= value && value >= KEYS_NAME[KEY_F]) || 
                    (KEYS_NAME[KEY_a] <= value && value <= KEYS_NAME[KEY_f] )) {

                if (y + 1 <= y_max) y++;

                if (current_pos < 3) {
                    buffer[current_pos++] = value;
                    rk_mytermregime(1, 50, 1, 1, 1);
                    printf("%c", value);
                    mt_gotoXY(x, y);
                }
            }

            else if (value == KEYS_NAME[KEY_ENTER]) {
                sc_icounterSet(rk_hex_to_dec(buffer));
                sc_TermUpdate();
                break;
            }

            else if (value == KEYS_NAME[KEY_ESC]) {
                sc_TermUpdate();
                break;
            }

            if(value == KEYS_NAME[KEY_ESC])
                break;
        }
    }

    else if(value == KEYS_NAME[KEY_ENTER] && interactive_mode){
        char buffer[6];
        buffer[5] = '\0';
        rk_command_to_string(buffer);
        int current_pos = 5;
        int new_value;

        int x, y = 0;

        x = command_counter / 10 + 2;
        y = (command_counter % 10) * 7 + 7;

        int y_min = y - 5;
        int y_max = y;

        while(1){

            mt_gotoXY(x, y);

            rk_mytermregime(1, 50, 1, 0, 1);

            rk_readkey(&value);

            if(value == KEYS_NAME[KEY_BACKSPACE]){

                if(current_pos != 0)
                    buffer[--current_pos] = ' ';

                if(y - 1 >= y_min)
                    mt_gotoXY(x, y--);

                else
                    mt_gotoXY(x, y);

                printf(" ");
            }

            if(value == KEYS_NAME[KEY_RIGHT]){
                if(y + 1 <= y_max){
                    current_pos++;
                    y++;
                }
                
            }

            if(value == KEYS_NAME[KEY_LEFT]){
                if(y - 1 > y_min){
                    current_pos--;
                    y--;
                }
            }

            if((KEYS_NAME[KEY_a] <= value && value <= KEYS_NAME[KEY_f]) || (KEYS_NAME[KEY_A] <= value && value <= KEYS_NAME[KEY_F]) || value == KEYS_NAME[KEY_PLUS] || 
                value == KEYS_NAME[KEY_MINUS] || (KEYS_NAME[KEY_0] <= value && value <= KEYS_NAME[KEY_9])){

                if(y + 1 <= y_max)
                    y+=1;

                if(current_pos < 5){

                    buffer[current_pos++] = value;
                    rk_mytermregime(1, 50, 1, 1, 1);
                    mt_gotoXY(x,y);
                    printf("%c", value);
                }
            }
            
            if(value == KEYS_NAME[KEY_ESC]){
                sc_TermUpdate();
                break;
            }
                

            if(value == KEYS_NAME[KEY_ENTER]){
                char ubuffer[5];

                strcpy(ubuffer, buffer + 1);

                mt_gotoXY(30, 40);
                printf("%d\n", rk_hex_to_dec(ubuffer));
                printf("%s", ubuffer);

                if(buffer[0] == '+')
                    sc_memorySet(command_counter, rk_hex_to_dec(ubuffer));
                else if(buffer[0] == '-')
                    sc_memorySet(command_counter, -rk_hex_to_dec(ubuffer));
        
                sc_TermUpdate();

                break;
            }

        }
    }
}

    rk_mytermregime(0, 50, 1, 1, 1);

}