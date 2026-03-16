x <- c(1, 5, 2, 2, 9)
y <- c(2, 7, 5, 5, 3)
max_val <- max(c(x, y))
tab_x <- tabulate(x, nbins = max_val)
tab_y <- tabulate(y, nbins = max_val)
tab_x
tab_y
which(tab_x > 0 & tab_y > 0)
