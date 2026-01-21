#!/bin/bash

# 1. Sprawdzamy, czy użytkownik podał argument (nazwę pliku)
if [ -z "$1" ]; then
    echo "Błąd: Nie podano pliku wejściowego."
    echo "Użycie: $0 <nazwa_pliku>"
    exit 1
fi

FILE="$1"

# 2. Sprawdzamy, czy podany plik faktycznie istnieje
if [ ! -f "$FILE" ]; then
    echo "Błąd: Plik '$FILE' nie istnieje."
    exit 1
fi

# 3. Wykonanie sed na podanym pliku
# '/^$/d' usuwa puste linie
# "$FILE" to zmienna zawierająca nazwę pliku z pierwszego argumentu
sed '/^$/d' "$FILE"
