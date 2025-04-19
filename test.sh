#!/bin/bash

echo "Нажмите клавишу (или Ctrl+C для выхода):"

while true; do
    # Читаем клавишу в RAW-режиме (без обработки терминалом)
    IFS= read -rsn1 key

    # Если нажата ESC, проверяем, не является ли это началом последовательности
    if [[ "$key" == $'\e' ]]; then
        # Читаем остальные символы (если есть)
        IFS= read -rsn2 -t 0.1 rest
        key+="$rest"
    fi

    # Выводим HEX-представление
    echo -n "Клавиша: "
    printf "%q" "$key"  # Вывод в escape-формате
    echo -ne "\nHEX: "
    hexdump -C <<< "$key"  # Вывод в HEX
    echo "---"
done
