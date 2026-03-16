approxinvert <- function(f, y, a, b, k = 100){
  x_vals <- seq(a, b, length.out = k)
  f_vals <- f(x_vals)
  f_inv <- approxfun(x = f_vals, y = x_vals)
  f_inv(y)
}
# Definiujemy funkcję wykładniczą
f_test <- function(x) exp(x)

# Ustawiamy dziedzinę od 0 do 5
a <- 0
b <- 5

# Wektor punktów (y), dla których szukamy x
y_test <- c(1, exp(1), exp(2)) # Spodziewamy się odpowiedzi: 0, 1, 2
y_test
# Wywołujemy naszą funkcję
wyniki_przyblizone <- approxinvert(f = f_test, y = y_test, a = a, b = b, k = 100)

print(wyniki_przyblizone)
