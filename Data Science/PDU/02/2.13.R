wystarczy <- function(lista, r, R, fun) {
  # 1. Aplikujemy funkcję 'fun' do każdego wektora z podanej listy.
  # sapply zwróci nam zwykły wektor wyników.
  wartosci <- sapply(lista, fun)
  
  # 2. Tworzymy wektor logiczny sprawdzający, czy wartości mieszczą się w przedziale [r, R].
  # Pamiętamy o operatorze logicznym '&' (AND).
  czy_wystarczy <- wartosci >= r & wartosci <= R
  
  # 3. Zwracamy podzbiór oryginalnej listy, używając indeksowania logicznego.
  wynik <- lista[czy_wystarczy]
  
  return(wynik)
}
