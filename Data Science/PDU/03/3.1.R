onehotenc <- function(t){
  k <- max(t)
  n <- length(t)
  M <- matrix(0, nrow = n, ncol = k)
  idx <- cbind(1:n, t)
  M[idx] <- 1
  return(M)
}
t_wektor <- c(1, 3, 2, 4, 1)
R_macierz_vec <- onehotenc(t_wektor)
print(R_macierz_vec)
