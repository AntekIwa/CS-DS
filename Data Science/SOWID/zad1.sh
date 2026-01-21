#!/bin/bash

# Sprawdzenie, czy podano dwa argumenty
if [ "$#" -ne 2 ]; then
    echo "Użycie: $0 plik1.json plik2.json"
    exit 1
fi

FILE1=$1
FILE2=$2

# Sprawdzenie, czy jq jest zainstalowane
if ! command -v jq &> /dev/null; then
    echo "Błąd: Narzędzie 'jq' nie jest zainstalowane. Zainstaluj je (np. apt install jq)."
    exit 1
fi

echo "--- Porównywanie plików: $FILE1 i $FILE2 ---"

# Używamy jq z flagą -S (sort keys) 
# diff -u pokazuje różnice w formacie unified (czytelnym dla człowieka)
# --color=auto koloruje wyjście
diff -u --color=auto <(jq -S . "$FILE1") <(jq -S . "$FILE2")

# Sprawdzenie kodu wyjścia diffa
if [ $? -eq 0 ]; then
    echo "--- Pliki są identyczne logicznie ---"
else
    echo "--- Znaleziono różnice (powyżej) ---"
fi
