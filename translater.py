from array import *
import os

commands = {
    "NOP": 0x00,
    "CPUINFO": 0x01,
    "READ": 0x0A,
    "WRITE": 0x0B,
    "LOAD": 0x14,
    "STORE": 0x15,
    "ADD": 0x1E,
    "SUB": 0x1F,
    "DIVIDE": 0x20,
    "MUL": 0x21,
    "JUMP": 0x28,
    "JNEG": 0x29,
    "JZ": 0x2A,
    "HALT": 0x2B,
    "NOT": 0x33,
    "AND": 0x34,
    "OR": 0x35,
    "XOR": 0x36,
    "JNS": 0x37,
    "JC": 0x38,
    "JNC": 0x39,
    "JP": 0x3A,
    "JNP": 0x3B,
    "CHL": 0x3C,
    "SHR": 0x3D,
    "RCL": 0x3E,
    "RCR": 0x3F,
    "NEG": 0x40,
    "ADDC": 0x41,
    "SUBC": 0x42,
    "LOGLC": 0x43,
    "LOGRC": 0x44,
    "RCCL": 0x45,
    "RCCR": 0x46,
    "MOVA": 0x47,
    "MOVR": 0x48,
    "MOVCA": 0x49,
    "MOVCR": 0x4A,
    "ADDC2": 0x4B,  
    "SUBC2": 0x4C 
}

def delete_extra_space(line):
    cleaned = ' '.join(line.split())
    cleaned.strip()
    return cleaned

print("Введите название файла: ")

result = array('i', [0] * 128)

filename = input()

with open("tst.txt", "r") as file:
    for line in file:
        clean_line = delete_extra_space(line)

        if(len(clean_line.split(" ")) != 3):
            print(f"Ошибка в строке: ${clean_line}")
            exit()

        address, command, operand = clean_line.split(" ")
        
        if(int(address) < 0 or int(address) >= 128):
            print(f"Ошибка в строке: {clean_line}")
            exit()

        if(command not in commands):
            print(f"Ошибка в строке: {clean_line}")
            exit()

        if(int(operand) < 0 or int(operand) >= 128):
            print(f"Ошибка в строке: {clean_line}")
            exit()

        command_bin = bin(int(commands[command]))[2:]

        command_bin = "0" * (7 - len(command_bin)) + command_bin

        operand_bin = bin(int(operand))[2:]

        operand_bin = "0" * (7 - len(operand_bin)) + operand_bin

        full_command = int("0" + command_bin + operand_bin, 2)

        result[int(address)] = full_command

with open("program.o", "wb") as bin_file:
    result.tofile(bin_file)
        

        
