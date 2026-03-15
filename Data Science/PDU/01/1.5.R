factorial2 <- function(n){
  if(n == 0){
    return(1)
  }
  return(factorial2(n - 1)*n)
}
factorial2(6)
factorial_stirling <- function(n){
  ((n/exp(1))^n) * sqrt(2*pi*n) 
}
factorial_stirling(6)
