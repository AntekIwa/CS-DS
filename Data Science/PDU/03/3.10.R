zwin <- function(df) {
  # 1. Wyciągamy nazwy poziomów z obu kolumn czynnikowych
  poziomy_wierszy <- levels(df[[2]])
  poziomy_kolumn <- levels(df[[3]])
  
  # Pobieramy wymiary macierzy
  n <- length(poziomy_wierszy)
  m <- length(poziomy_kolumn)
  
  # 2. Tworzymy pustą macierz o rozmiarze n x m
  # Używamy typu danych z pierwszej kolumny (na wypadek, gdyby to nie były liczby)
  wynikowa_macierz <- matrix(NA, nrow = n, ncol = m)
  
  # 3. Przekształcamy czynniki na ich ukryte wartości liczbowe (indeksy)
  # as.integer() dla czynnika zwraca pozycję poziomu (np. 1, 2, 3...)
  indeksy_wierszy <- as.integer(df[[2]])
  indeksy_kolumn <- as.integer(df[[3]])
  
  # 4. Wypełniamy macierz za pomocą tzw. indeksowania macierzowego
  # cbind tworzy macierz współrzędnych [wiersz, kolumna] dla każdej wartości z df[[1]]
  wynikowa_macierz[cbind(indeksy_wierszy, indeksy_kolumn)] <- df[[1]]
  
  # 5. Ustawiamy atrybut dimnames
  dimnames(wynikowa_macierz) <- list(poziomy_wierszy, poziomy_kolumn)
  
  return(wynikowa_macierz)
}
