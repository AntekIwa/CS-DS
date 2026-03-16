softmax_and_decode <- function(X){
  X_exp <- exp(X)
  X_soft <- X_exp/rowSums(X_exp)
  decoded <- max.col(X_soft)
  return(decoded)
}
set.seed(42) # Dla powtarzalności wyników
X <- matrix(rnorm(12), nrow = 3, ncol = 4)

cat("Oryginalna macierz X:\n")
print(X)
rowSums(X)
# Wywołujemy funkcję
wynik <- softmax_and_decode(X)

cat("\nOdkodowany wektor n-elementowy:\n")
print(wynik)
