#pragma once

#define enable_command_size 40

enum KEYS{
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_a,
    KEY_b,
    KEY_c,
    KEY_d,
    KEY_e,
    KEY_f,
    KEY_g,
    KEY_h,
    KEY_i,
    KEY_j,
    KEY_k,
    KEY_l,
    KEY_m,
    KEY_n,
    KEY_o,
    KEY_p,
    KEY_q,
    KEY_r,
    KEY_s,
    KEY_t,
    KEY_u,
    KEY_v,
    KEY_w,
    KEY_x,
    KEY_y,
    KEY_z,

    KEY_TOP,
    KEY_BOTTOM,
    KEY_LEFT,
    KEY_RIGHT,

    KEY_ENTER,

    KEY_PLUS,
    KEY_MINUS,

    KEY_ESC,

    KEY_BACKSPACE,

    KEY_F2,
    KEY_F4,
};

extern const int KEYS_NAME[];

extern const int enable_command[];

extern int interactive_mode;

extern struct termios saved_attributes;

int rk_readkey(enum KEYS *value);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue(int *value, int timeout);
int rk_hex_to_dec(char *hex);
void rk_command_to_string(char *hex);
void rk_accumulator_to_string(char* hex);
void rk_counter_to_string(char *hex);
int rk_string_dec_to_dec(char *num);