#include "../include/myBigChars.h"
#include "../include/myTerm.h"

int switch_table(void){
    char* switch_table = "\033(0";

    write(1,switch_table, strlen(switch_table));

    return 0;
}

int return_table(void){
    char* switch_table = "\033(B";

    write(1,switch_table, strlen(switch_table));

    return 0;
}

int bc_strlen(char *str) {
    int count_char = 0;
    if (!str)
        return -1;

    while (*str) {
        if ((*str & 0x80) == 0) {  // Латиница/цифра
            count_char++;
            str++;
        } else if ((*str & 0xE0) == 0xC0) {  // Кириллица
            count_char++;
            str += 2;
        } else {
            return 0;
        }
    }

    return count_char;
}

int bc_printA(char *str) {
    if (!str) {
        return -1;
    }

    switch_table();

    for (int i = 0; i < bc_strlen(str); i++) {
        printf("%c ", str[i]);
    }

    return_table();

    return 0;
}

int bc_box(int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg, char *header, enum colors header_fg, enum colors header_bg) {
    if (!(x2 > 1 && y2 > 1 && box_fg < COLORS_COUNT && box_bg < COLORS_COUNT && header_fg < COLORS_COUNT && header_bg < COLORS_COUNT)) {
        return -1;
    }

    mt_setbgcolor(box_bg);
    mt_setfgcolor(box_fg);

    char tl = 'l', tr = 'k', bl = 'm', br = 'j';
    char hl = 'q', vl = 'x';

    switch_table();

    mt_gotoXY(x1, y1);
    putchar(tl);

    for (int i = 1; i < y2 - 1; i++)
        putchar(hl);

    mt_gotoXY(x1, y1 + y2 - 1);
    putchar(tr);

    for (int i = 1; i < x2 - 1; i++) {
        mt_gotoXY(x1 + i, y1);
        putchar(vl);

        mt_gotoXY(x1 + i, y1 + y2 - 1);
        putchar(vl);
    }

    mt_gotoXY(x1 + x2 - 1, y1);
    putchar(bl);

    for (int i = 1; i < y2 - 1; i++)
        putchar(hl);

    mt_gotoXY(x1 + x2 - 1, y1 + y2 - 1);
    putchar(br);

    fflush(stdout);
    return_table();

    if (header) {
        int len = bc_strlen(header);
        if (len > y2 - 2)
            len = y2 - 2;

        int header_x = x1;
        int header_y = y1 + (y2-len) /2;
        mt_setfgcolor(header_fg);
        mt_setbgcolor(header_bg);
        mt_gotoXY(header_x, header_y);
        fflush(stdout);
        return_table();
        fflush(stdout);
        printf("%s", header);
        fflush(stdout);
        return_table();
    }

    fflush(stdout);
    return_table();
    fflush(stdout);

    return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
    if (x < 0 || y < 0 || y >= BIGCHAR_WIDTH || x >= BIGCHAR_WIDTH || !big || (value != 0 && value != 1)) {
        return -1;
    }

    int index = x / 4;
    int bit_position = y + (x % 4) * 8;

    if (value) {
        big[index] |= (1 << bit_position);
    } else {
        big[index] &= ~(1 << bit_position);
    }

    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
    if (x < 0 || y < 0 || y >= BIGCHAR_WIDTH || x >= BIGCHAR_WIDTH || !big || !value) {
        return -1;
    }

    int index = x / 4;
    int bit_position = y + (x % 4) * 8;

    *value = (big[index] >> bit_position) & 1;

    return 0;
}

int bc_printbigchar(int *big, int x, int y, enum colors fg, enum colors bg) {
    switch_table();
    mt_setbgcolor(bg);
    mt_setfgcolor(fg);
    for (int i = 0; i < BIGCHAR_HEIGHT + 1; i++) {
        mt_gotoXY(x + i, y);
        for (int j = 0; j < BIGCHAR_WIDTH; j++) {
            int value;
            bc_getbigcharpos(big, i, j, &value);
            printf("%c", value ? ACS_CKBOARD : ' ');
        }
    }

    return_table();
    mt_setdefaultcolor();
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
    if (fd < 3 || !big) {
        return -1;
    }

    int bytes_written = write(fd, big, count * 2 * sizeof(int));
    if (bytes_written != count * 2 * sizeof(int)) {
        return -1;
    }

    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
    if (fd < 3 || !big || !count || need_count <= 0) {
        if (count)
            *count = 0;
        return -1;
    }

    int bytes_read = read(fd, big, need_count * 2 * sizeof(int));
    if (bytes_read < 0) {
        *count = 0;
        return -1;
    }

    *count = bytes_read / (2 * sizeof(int));
    return 0;
}