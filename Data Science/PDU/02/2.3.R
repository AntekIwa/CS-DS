x <- c(1, 2, 1, 4, 3, 4, 1)
y <- match(x,x) == seq_along(x)
x[y]
