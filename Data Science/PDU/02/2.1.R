calkaMonteCarlo <- function(f, a, b, n = 1000) {
  if(f(a) < 0 || f(b) < 0){
    stop("Wartości funkcji na krańcach przedziału f(a) i f(b) muszą być nieujemne.")
  }
  fmin <- min(f(a), f(b))
  fmax <- max(f(a), f(b))
  x1 <- runif(n, min = a, max = b)
  x2 <- runif(n, min = fmin, max = fmax)
  frakcja <- mean(x2 <= f(x1))
  pole_obszaru <- (b - a) * (fmax - fmin)
  wynik_skalowany <- frakcja * pole_obszaru
  calka <- wynik_skalowany + (b - a) * fmin
  return(calka)
}

set.seed(123)

# Przykład 1
f <- function(x) sin(x)
a <- 0
b <- 1
n <- 10000
calkaMonteCarlo(f, a, b, n)
# Oczekiwany wynik: ok. 0.461042

# Przykład 2
f <- function(x) x + 1
calkaMonteCarlo(f, a, b, n)
# Oczekiwany wynik: ok. 1.5101

# Przykład 3
f <- function(x) x^2 + 2
calkaMonteCarlo(f, a, b, n)
# Oczekiwany wynik: ok. 2.3304