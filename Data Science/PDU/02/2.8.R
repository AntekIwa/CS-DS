distance <- function(p, a, b){
  licznik <- abs(sum(a*p) + b)
  mianownik <- sqrt(sum(a^2))
  return(licznik/mianownik)
}
# Przykład 1:
# Punkt p = (2, -2, 0.5), wektor a = (2, 1, 4), b = -4
wynik1 <- distance(p = c(2, -2, 0.5), a = c(2, 1, 4), b = -4)
print(wynik1)
# Oczekiwany wynik: 0 
# (To oznacza, że ten punkt leży idealnie NA tej prostej/płaszczyźnie!)

# Przykład 2:
# Punkt p = (0, 0), wektor a = (1, 1), b = -2.0
wynik2 <- distance(p = c(0, 0), a = c(1, 1), b = -2.0)
print(wynik2)
# Oczekiwany wynik: 1.414214 (czyli po prostu pierwiastek z 2)