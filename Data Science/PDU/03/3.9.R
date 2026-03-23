rozwin <- function(macierz, nazwy_kolumn) {
  wiersze <- rownames(macierz)
  kolumny <- colnames(macierz)
  
  # 2. Tworzymy wszystkie kombinacje wierszy i kolumn.
  # Funkcja expand.grid układa je w dokładnie takiej samej kolejności, 
  # w jakiej funkcja as.vector "rozwija" macierz (czyli idąc kolumnami od góry do dołu).
  kombinacje <- expand.grid(wiersze, kolumny)
  
  # 3. Składamy ramkę danych. Zgodnie z przykładem, kolejność to: 
  # wartości macierzy, zmienna z kolumn (gdzie), zmienna z wierszy (kiedy).
  wynik <- data.frame(
    wartosci = as.vector(macierz),
    zmienna_kolumnowa = kombinacje[[2]], # np. "N.Amer", "Europe"
    zmienna_wierszowa = kombinacje[[1]]  # np. "1951", "1956"
  )
  
  # 4. Zmieniamy nazwy kolumn w ramce na te podane przez użytkownika
  colnames(wynik) <- nazwy_kolumn
  
  return(wynik)
}
