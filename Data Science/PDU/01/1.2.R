pearson <- function(x, y){
  n <- length(x)
  r <- (1/(n - 1) * sum(((x - mean(x))/sd(x))*((y - mean(y))/sd(y))))
  return(r)
}
x1 <- rnorm(20, 0, 1)
y1 <- 10 * x1 + 2
pearson(x1, y1)
x2 <- rnorm(20, 0, 1)
y2 <- -4 * x2 + 1
pearson(x2, y2)
x <- as.numeric(readLines("zad_pearson_x.txt"))
y <- as.numeric(readLines("zad_pearson_y.txt"))
pearson(x, y)
