import sys
from array import array

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
    return ' '.join(line.strip().split())

def main():
    if len(sys.argv) != 3:
        print("Использование: sat файл.sa файл.o")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    result = array('i', [0] * 128)

   
    with open(input_file, "r") as file:
        for line_num, line in enumerate(file, 1):
            clean_line = delete_extra_space(line)

            if len(clean_line.split(" ")) != 3:
                print(f"Ошибка в строке {line_num}: {clean_line}")
                sys.exit(1)

            address, command, operand = clean_line.split(" ")

            address = int(address)
            operand = int(operand)
            
            if not (0 <= address < 128):
                print(f"Недопустимый адрес в строке {line_num}: {clean_line}")
                sys.exit(1)

            if command not in commands:
                print(f"Неизвестная команда в строке {line_num}: {clean_line}")
                sys.exit(1)

            if not (0 <= operand < 128):
                print(f"Недопустимый операнд в строке {line_num}: {clean_line}")
                sys.exit(1)

            command_code = commands[command]

            full_command = (command_code << 7) | operand

            result[address] = full_command

    with open(output_file, "wb") as bin_file:
        result.tofile(bin_file)

    print(f"Трансляция завершена. Результат сохранён в '{output_file}'.")

if __name__ == '__main__':
    main()

