merge_string_list <- function(x, sep = ""){
  if (!is.list(x)) {
    stop("Błąd: Argument 'x' musi być listą!")
  }
  if (!all(sapply(x, is.character))) {
    stop("Błąd: Wszystkie elementy listy muszą być wektorami napisów (character)!")
  }
  plaski_wektor <- unlist(x)
  wynik <- paste(plaski_wektor, collapse = sep)
  return(wynik)
}
# --- TEST 1: Prawidłowa lista ---
lista_dobra <- list(c("Ala", "ma"), c("bardzo", "fajnego"), "kota.")
cat(merge_string_list(lista_dobra, sep = " "), "\n")
# Oczekiwany wynik: Ala ma bardzo fajnego kota.

# --- TEST 2: Inny separator ---
lista_liter <- list(c("A", "B"), c("C", "D"))
cat(merge_string_list(lista_liter, sep = "-"), "\n")
# Oczekiwany wynik: A-B-C-D

# --- TEST 3: Lista z błędnymi danymi (liczby zamiast napisów) ---
lista_zla <- list(c("Napis", "Napis"), c(1, 2, 3))
# merge_string_list(lista_zla) 
# Zwróci: Error: Błąd: Wszystkie elementy listy muszą być wektorami napisów (character)!

# --- TEST 4: Zły typ wejściowy (zwykły wektor zamiast listy) ---
merge_string_list(c("a", "b", "c"))
# Zwróci: Error: Błąd: Argument 'x' musi być listą!
library(jsonlite)
dane_json_1 <- read_json("zad_merge_string_list-1.json", simplifyVector = TRUE)
dane_json_2 <- read_json("zad_merge_string_list-2.json", simplifyVector = TRUE)

# Łączymy napisy wczytane z plików
wynik_json_1 <- merge_string_list(dane_json_1, sep = " ")
wynik_json_2 <- merge_string_list(dane_json_2, sep = "\n")
print(wynik_testowy)
# print() pokaże "surowy" kod napisu, włącznie ze znacznikami i cudzysłowami: 
# [1] "Linia pierwsza\nLinia druga\tWcięcie"

cat(wynik_testowy)