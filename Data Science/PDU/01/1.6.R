taylor <- function(x, m){
  n <- 0:m
  licznik <- factorial(2*n)
  mianownik <- (4^n)*(factorial(n)^2)*(2*n + 1)
  wyrazy <- (licznik / mianownik) * (x^(2 * n + 1))
  return(sum(wyrazy))
}

taylor_log <- function(x, m){
  n <- 0:m
  log_C <- lfactorial(2*n) - n*log(4)- 2 * lfactorial(n) - log(2 * n + 1)
  wyrazy <- exp(log_C) * (x^(2 * n + 1))
  
  # Zwracamy sumę
  return(sum(wyrazy))
}
x <- 0.5

# Dla m = 10
roznica_10 <- taylor_log(x, 10) - asin(x)
print(paste("Dla m = 10 różnica to:", roznica_10))

# Dla m = 100
roznica_100 <- taylor_log(x, 100) - asin(x)
print(paste("Dla m = 100 różnica to:", roznica_100))

# Dla m = 1000
roznica_1000 <- taylor_log(x, 1000) - asin(x)
print(paste("Dla m = 1000 różnica to:", roznica_1000))
