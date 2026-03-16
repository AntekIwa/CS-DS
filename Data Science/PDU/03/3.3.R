bounding_hyperrectangle <- function(X){
  b1 <- apply(X, 2, min)
  b2 <- apply(X, 2, max)
  B <- rbind(b1, b2)
  rownames(B) <- c("min", "max")
  return(B)
}
# Tworzymy przykładową macierz X wymiaru 5x3 (5 punktów w 3 wymiarach)
set.seed(123)
X <- matrix(sample(1:50, 15), nrow = 5, ncol = 3)

cat("Macierz punktów X (n=5, d=3):\n")
print(X)

# Wyznaczamy przedział wielowymiarowy
B <- bounding_hyperrectangle(X)

cat("\nMacierz ograniczająca B (2 x d):\n")
print(B)
