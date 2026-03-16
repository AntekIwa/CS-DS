gendyskr <- function(n, x, p) {
  if (abs(sum(p) - 1) > 1e-8) {
    warning("Elementy wektora p nie sumują się do 1. Zostaną unormowane.")
    p <- p / sum(p) # Normowanie (dzielimy przez sumę, by razem dawały 1)
  }
  u <- runif(n)
  przedzialy <- c(0, cumsum(p))
  m <- findInterval(u, przedzialy, left.open = TRUE)
  x[m]
}
# Wartości (nasze x)
wygrane <- c(10, 50, -20)

# Prawdopodobieństwa (nasze p) - celowo zepsute, sumują się do 10 zamiast do 1
prawdopodobienstwa <- c(2, 1, 7) 

# Generujemy 10 obserwacji
set.seed(42)
losowanie <- gendyskr(n = 10, x = wygrane, p = prawdopodobienstwa)

print(losowanie)
