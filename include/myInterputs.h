#pragma once

extern int halt_flag;

int ALU (int command, int operand);
void IRC (int signum);
void CU ();
void setup_timer ();
void disable_timer ();
