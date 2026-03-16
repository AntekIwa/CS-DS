find_moda <- function(x){
  x_sort <- sort(x)
  kompresja <- rle(x_sort)
  idx_mody <- which.max(kompresja$lengths)
  moda <- kompresja$values[idx_mody]
  return(moda)
}
wektor_testowy <- c(3, 1, 2, 3, 4, 3, 1)

# Wywołujemy funkcję
wynik <- find_moda(wektor_testowy)
print(wynik)
# Oczekiwany wynik: 3