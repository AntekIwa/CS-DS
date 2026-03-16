movingavg <- function(x, k) {
  n <- length(x)
  if(k >= n || k %% 2 == 0){
    stop("zle dane")
  }
  cs <- c(0, cumsum(x))
  suma <- cs[(k + 1):(n + 1)] - cs[1:(n - k + 1)]
  suma/k
}
# Przykładowy szereg czasowy (10 elementów)
x_szereg <- c(2, 4, 6, 8, 12, 14, 18, 20, 22, 24)
k_okno <- 3 # Nieparzysta liczba naturalna


cat("Oryginalny wektor x:\n")
print(x_szereg)

wynik <- movingavg(x_szereg, k_okno)

cat("\nŚrednia ruchoma (k =", k_okno, "):\n")
print(wynik)
