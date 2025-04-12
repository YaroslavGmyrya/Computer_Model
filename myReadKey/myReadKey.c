#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include "../include/myReadKey.h"
 #include "../include/MySimpleComputer.h"

int rk_readkey(enum KEYS *value){

    char buf[200];

    int read_bytes = read(0, buf, 199);

    if(!(read_bytes > 0))
        return -1;
    
    if(read_bytes == 1)
        *value = (enum KEYS)buf[0];

    if(read_bytes == 3){
        switch((enum KEYS)buf[2]){
            case 0x41: *value = KEYS_NAME[KEY_TOP];    return 0;
            case 0x42: *value = KEYS_NAME[KEY_BOTTOM];  return 0;
            case 0x43: *value = KEYS_NAME[KEY_RIGHT]; return 0;
            case 0x44: *value = KEYS_NAME[KEY_LEFT];  return 0;
            case 0x51: *value = KEYS_NAME[KEY_F2];  return 0;
            case 0x53: *value = KEYS_NAME[KEY_F4];  return 0;
        }
    }

    return 0;
    
}

int rk_mytermsave(void) {
    if (tcgetattr(0, &saved_attributes) != 0) {
        return -1;
    }
    return 0;
}

int rk_mytermrestore(void) {
    if (tcsetattr(0, TCSANOW, &saved_attributes) != 0) {
        return -1;
    }
    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
    struct termios tattr;
    
    if (tcgetattr(0, &tattr) != 0) {
        return -1;
    }

    if (regime) {

        tattr.c_lflag &= ~(ICANON | ECHO);
        tattr.c_cc[VTIME] = vtime;
        tattr.c_cc[VMIN] = vmin;
        
        if (echo) tattr.c_lflag |= ECHO;
        else tattr.c_lflag &= ~ECHO;
        
        if (sigint) tattr.c_lflag |= ISIG;
        else tattr.c_lflag &= ~ISIG;
    } else {
        tattr.c_lflag |= ICANON;
        if (echo) tattr.c_lflag |= ECHO;
        else tattr.c_lflag &= ~ECHO;
    }

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr) != 0) {
        return -1;
    }
    return 0;
}

int rk_readvalue(int *value, int timeout) {

    int fd, read_chars;
    char buf[200];

    fd = open("/dev/tty", O_WRONLY);

    if (fd == -1){
        return 1;
    }

    if ((read_chars = read(0, buf, 199)) > 0){
        if(read_chars == 1){
            write(fd, buf[0],1);
        }
    } 
    else {
        write (fd, "Ошибка", 6);
    }

    close (fd);

    return 0;

}

int rk_hex_to_dec(char *hex) {

    int dec = 0;
    int len = strlen(hex);
    
    for (int i = 0; i < len; i++) {
        char c = tolower(hex[i]);
        int value;
        
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = 10 + (c - 'a');
        } else {
            return -1;
        }
        
        dec = dec * 16 + value;
    }

        return dec;
}

void rk_command_to_string(char *hex) {
    int value, sign, command, operand;
    sc_memoryGet(command_counter, &value);
    sc_commandDecode(value, &sign, &command, &operand);
    if(sign)
        sprintf(hex, "-%x%x", command, operand); 
    else
        sprintf(hex, "+%x%x", command, operand); 
}

void rk_accumulator_to_string(char *hex) {
    int value;
    sc_accumulatorGet(&value);
    
    if(value & (1 << 14))
        sprintf(hex, "-%04x", value);
    else
        sprintf(hex, "+%04x", value);
   
}

void rk_counter_to_string(char *hex) {
    int value;
    sc_icounterGet(&value);
    
    sprintf(hex, "%03d", value);
}

int rk_string_dec_to_dec(char *num) {
    int result = 0;
    while (*num) {
        result = result * 10 + (*num - '0');
        num++;
    }
    return result;
}
