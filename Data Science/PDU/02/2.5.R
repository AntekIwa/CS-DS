x <- c(1, 5, 2, 2, 9)
y <- c(2, 7, 5, 5, 3)
x_sort <- sort(x)
licznik <- findInterval(y, x_sort)
F_hat <- licznik / length(x)
F_hat
