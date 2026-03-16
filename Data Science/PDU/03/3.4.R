euclidean_distances <- function(X, y) {
  diff_matrix <- sweep(X, 2, y, "-")
  sq_diff <- diff_matrix^2
  d <- sqrt(rowSums(sq_diff))
  return(d)
}
# Tworzymy macierz X wymiaru 4x3 (4 punkty w przestrzeni 3-wymiarowej)
X <- matrix(c(1, 2, 3,
              4, 5, 6,
              7, 8, 9,
              0, 0, 0), nrow = 4, byrow = TRUE)

# Definiujemy punkt y w R^3
y <- c(1, 1, 1)

cat("Macierz X:\n")
print(X)
cat("\nPunkt y:\n")
print(y)

# Obliczamy odległości
d_wektor <- euclidean_distances(X, y)

cat("\nWektor odległości d:\n")
print(d_wektor)
