import random
import sys

commands_basic = {
    "REM" : "NOP",
    "INPUT" : "READ",
    "LET" : "",
    "IF" : ["JNS", "JNEG", "JZ"],
    "GOTO" : "JUMP",
    "PRINT" : "WRITE",
    "END" : "HALT",
}

variables = {}

def delete_extra_space(line):
    return ' '.join(line.strip().split())

def main():
    random.seed(10)
    if len(sys.argv) != 3:
        print("Использование: sat файл.sa файл.o")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    current_line_number = 0

    num_line = 0

    with open(input_file, "r") as input, open(output_file, "w") as output:
        for line in input:
            line = delete_extra_space(line)
            split_line = line.split(" ")
            #num_line = int(split_line[0])

            if num_line % 10 != 0 or num_line < current_line_number or num_line >= 980:
                print(f"Неверный номер в строке: {line}")
                exit(1)

            current_line_number = num_line

            command = split_line[1]

            if command == "INPUT":
                if len(split_line) != 3:
                    print(f"Неверное число аргументов в строке : {line}")
                    exit(1)

                operand = split_line[2]

                if operand not in variables:
                    print(len(variables.values()))
                    if len(variables.values()) == 0:
                        new_address = 98

                    else:
                        new_address = max(variables.values())

                    if new_address == 127:
                        print(f"Нет свободной памяти под переменную {operand}")       
                        exit(1)                

                    variables[operand] = new_address + 1
                       
                output.write(f"{num_line // 10} {commands_basic[command]} {variables[operand]}\n")
                num_line += 10

            if command == "END":
                if len(split_line) != 2:
                    print(f"Неверное число аргументов в строке : {line}")
                    exit(1)

                output.write(f"{num_line // 10} {commands_basic[command]} {0}\n")
                num_line += 10

            if command == "PRINT":
                if len(split_line) != 3:
                    print(f"Неверное число аргументов в строке : {line}")
                    exit(1)

                operand = split_line[2]

                if operand not in variables:
                    print(f"Попытка вывести несуществующую переменную: {line}")
                    exit(1)
                
                output.write(f"{num_line // 10} {commands_basic[command]} {variables[operand]}\n")
                num_line += 10

            if command == "GOTO":
                if len(split_line) != 3:
                    print(f"Неверное кол-во аргументов в строке: {line}")
                    exit(1)

                next_hop_address = int(split_line[2])

                if next_hop_address > current_line_number or next_hop_address >= 98:
                    print(f"Попытка перейти на несуществующий адрес: {line}")
                    exit(1)

                output.write(f"{num_line // 10} {commands_basic[command]} {next_hop_address // 10}\n")
                num_line += 10

            if command == "IF":
                operand = split_line[2]
                
                if operand not in variables:
                    print(f"Попытка обратиться к несуществующей переменной: {line}")
                    exit(1)

                sign = split_line[3]

                if sign != "<" and sign != ">" and sign != "==":
                    print(f"Неверная операция в условном операторе: {line}")
                    exit(1)

                if split_line[4] != "0":
                    print(f"Попытка выполнить сравнение не с нулем: {line}")
                    exit(1)

                if split_line[5] != "GOTO":
                    print(f"Не указан адрес перехода: {line}")
                    exit(1)

                next_hop_address = int(split_line[6])
                
                if sign == "==":
                    output.write(f"{num_line // 10} LOAD {variables[operand]}\n")
                    num_line += 10
                    output.write(f"{num_line // 10} {commands_basic[command][2]} {next_hop_address // 10}\n")
                    num_line += 10
                
                if sign == ">":
                    output.write(f"{num_line // 10} LOAD {variables[operand]}\n")
                    num_line += 10
                    output.write(f"{num_line // 10} {commands_basic[command][0]} {next_hop_address // 10}\n")
                    num_line += 10

                if sign == "<":
                    output.write(f"{num_line // 10} LOAD {variables[operand]}\n")
                    num_line += 10
                    output.write(f"{num_line // 10} {commands_basic[command][1]} {next_hop_address // 10}\n")
                    num_line += 10

                #output.write(f"{num_line // 10} {commands_basic[command]} {variables[operand]}\n")

            if command == "LET":
                if len(split_line) != 7:
                    print(f"Неверный формат выражения: {line}")
                    exit(1)

                store, first_operand, sign, second_operand = split_line[2], split_line[4], split_line[5], split_line[6]

                if store not in variables:

                    if len(variables.values()) == 0:
                        new_address = 98

                    else:
                        new_address = max(variables.values())

                    if new_address == 127:
                        print(f"Нет свободной памяти под переменную {operand}")       
                        exit(1)                

                    variables[store] = new_address + 1

                if split_line[4] not in variables or split_line[6] not in variables:
                    print(f"Попытка выполнить операцию с необъявленными переменными: {line}")
                    exit(1)

                output.write(f"{num_line // 10} LOAD {variables[first_operand]}\n")
                num_line += 10

                if sign == "+":
                    output.write(f"{num_line // 10} ADD {variables[second_operand]}\n")
                    num_line += 10
                
                if sign == "-":
                    output.write(f"{num_line // 10} SUB {variables[second_operand]}\n")
                    num_line += 10

                if sign == "/":
                    output.write(f"{num_line // 10} DIVIDE {variables[second_operand]}\n")
                    num_line += 10

                if sign == "*":
                    output.write(f"{num_line // 10} MUL {variables[second_operand]}\n")
                    num_line += 10

                output.write(f"{num_line // 10} STORE {variables[store]}\n")
                num_line += 10

    print(f"Трансляция завершена. Результат сохранён в '{output_file}'.")

if __name__ == '__main__':
    main()

