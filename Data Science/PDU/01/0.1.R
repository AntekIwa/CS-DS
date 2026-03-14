set.seed(123)
x <- round(rnorm(20, 0, 1), 2)
x >= 2
x[(x  >= -2 & x <= -1) | (x >= 1 & x <= 2)]
sum(x>=0)
mean(x>=0)
mean(abs(x))
x[which.min(abs(x))]
max(x)
x[which.max(abs(x))]
x_znormalizowane <- (x - min(x)) / (max(x) - min(x))
print(x_znormalizowane)

ifelse(x >= 0, "nieujemna", "ujemna")
ifelse(x < -1, "maly", ifelse(abs(x) <= 1, "sredni","duzy"))
floor(x) + 0.5
  
