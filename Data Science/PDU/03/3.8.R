# Wczytanie tylko pakietu z danymi
library(fueleconomy)

# Kopiujemy zbiór do nowej zmiennej, żeby na nim pracować
wynik <- vehicles

# Krok 1: Zamiana jednostek z mpg na l/100km
wynik$cty <- 235.214583 / wynik$cty
wynik$hwy <- 235.214583 / wynik$hwy

# Krok 2: Standaryzacja w grupach (tworzenie nowych kolumn z_cty i z_hwy)
# Funkcja ave() domyślnie liczy średnią, ale jeśli podamy jej własną funkcję (FUN), 
# to policzy dokładnie to, co chcemy.

wynik$z_cty <- ave(wynik$cty, wynik$class, FUN = function(x) {
  (x - mean(x, na.rm = TRUE)) / sd(x, na.rm = TRUE)
})

wynik$z_hwy <- ave(wynik$hwy, wynik$class, FUN = function(x) {
  (x - mean(x, na.rm = TRUE)) / sd(x, na.rm = TRUE)
})
