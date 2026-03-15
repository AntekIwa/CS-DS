spearman <- function(x, y){
  n <- length(x)
  rx <- rank(x)
  ry <- rank(y)
  d <- rx - ry
  g <- 1 - ((6*sum(d^2))/(n*(n^2 - 1)))
  k <- 1 - pt(q = g*sqrt((n - 2)/(1 - g^2)), df = n - 2)
  return(list(g, k))
}

# Generujemy przykładowe dane
set.seed(123)
wektor_x <- rnorm(20)
# Tworzymy wektor y lekko skorelowany z x
wektor_y <- wektor_x + rnorm(20, mean = 0, sd = 0.5) 

spearman(wektor_x, wektor_y)
