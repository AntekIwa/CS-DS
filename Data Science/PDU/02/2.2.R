sample2 <- function(x, k, replace = TRUE){
  if(replace == TRUE){
    x[ceiling(runif(k, min = 0, max = length(x)))]
  }
  else{
    x[order(runif(length(x)))[1:k]]
  }
}
x <- c('a', 'b', 'c')
k <- 2
sample2(x,k, replace = FALSE)
