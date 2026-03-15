kwinsor <- function(x, k){
  n <- length(x)
  if(k == 0){
    return(mean(x))
  }
  x_sort <- sort(x)
  dol <- x_sort[k + 1]
  gora <- x_sort[n - k]
  x_sort[1:k] <- dol
  x_sort[(n - k + 1) : n] <- gora
  return(mean(x_sort))
}