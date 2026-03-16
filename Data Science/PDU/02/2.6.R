sort_punkty <- function(n, m, wektor){
  punkty_macierz <- matrix(wektor, nrow = n, ncol = m, byrow = TRUE)
  odleglosc <- sqrt(colSums(punkty_macierz^2))
  kolejnosc <- order(odleglosc)
  posortowana_macierz <- punkty_macierz[, kolejnosc, drop = FALSE]
  wynik <- as.vector(t(posortowana_macierz))
  
  return(wynik)
}

wektor_testowy <- c(3, 0, 0, 4, 1, 0)
wynik <- sort_punkty(n = 2, m = 3, wektor = wektor_testowy)

print(wynik)
# Wynik z konsoli: 0 0 3 0 1 4