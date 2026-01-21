check_disk_health() {
    local drive_path=$1
    
    if [ -z "$drive_path" ]; then
        echo "Błąd: Podaj ścieżkę do urządzenia (np. /dev/sda lub /dev/sdb1)"
        return 1
    fi

    echo "Rozpoczynam test odczytu dla: $drive_path"

    # if=...        -> plik wejściowy (urządzenie)
    # of=/dev/null  -> plik wyjściowy (kosz, nigdzie nie zapisujemy)
    # bs=4M         -> wielkość bloku (przyspiesza odczyt)
    # status=progress -> pokazuje pasek postępu
    # conv=noerror,sync -> najważniejsze flagi!
    #    noerror: nie przerywamy przy błędzie odczytu (chcemy znaleźć wszystkie błędy)
    #    sync: uzupełnij błędne bloki zerami (dla zachowania ciągłości)
    
    sudo dd if="$drive_path" of=/dev/null bs=4M status=progress conv=noerror,sync
    
    local exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo "Zakończono: Nie wykryto krytycznych błędów I/O podczas czytania."
    else
        echo "Ostrzeżenie: dd zakończył działanie z kodem błędu. Sprawdź logi powyżej pod kątem 'Input/output error'."
    fi
}

# check_disk_health "/dev/sdb"
