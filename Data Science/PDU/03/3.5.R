x <- c(2, 3, 4, 5) # Oceny z Filozofii Bytu (FB) - wiersze
y <- c(2, 3, 4, 5) # Oceny z WF - kolumny

# Macierz prawdopodobieństw rozkładu łącznego (X, Y)
P <- matrix(c(
  0,    0.01, 0.1,  0.2,
  0.01, 0.05, 0.03, 0.1,
  0.1,  0.03, 0.05, 0.01,
  0.2,  0.1,  0.01, 0
), nrow = 4, byrow = TRUE)

niezaleznosc <- function(x, y, p) {
  P_brzegX <- rowSums(p)
  P_brzegY <- colSums(p)
  P_oczekiwane <- outer(P_brzegX, P_brzegY, FUN = "*")
  isTRUE(all.equal(P, P_oczekiwane))
}
cat("Czy oceny z FB i WF są niezależne? ", niezaleznosc(x, y, P), "\n")

podstat <- function(x, y, P){
  P_brzeg_X <- rowSums(P)
  P_brzeg_Y <- colSums(P)
  EX <- sum(x, P_brzeg_X)
  EY <- sum(y, P_brzeg_Y)
  EX2 <- sum((x^2) * P_brzeg_X)
  EY2 <- sum((y^2) * P_brzeg_Y)
  VarX <- EX2 - EX^2
  VarY <- EY2 - EY^2
  EXY <- sum(outer(x, y) * P)
  CovXY <- EXY - (EX * EY)
  CorXY <- CovXY / sqrt(VarX * VarY)
  statystyki <- c(
    "E(X)" = EX,
    "E(Y)" = EY,
    "Var(X)" = VarX,
    "Var(Y)" = VarY,
    "Cov(X,Y)" = CovXY,
    "Cor(X,Y)" = CorXY
  )
  
  return(statystyki)
}
cat("\nPodstawowe statystyki rozkładu łącznego:\n")
print(podstat(x, y, P))
