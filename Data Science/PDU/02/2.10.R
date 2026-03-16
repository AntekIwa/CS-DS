x <- list(a=1:10,
          b=letters[1:5],
          c=sum,
          d=seq(0, 1, 0.01),
          e=list(e1=runif(20) < 0.2,
                 e2="Ala ma kota"))
x
x[c("a", "b")]
x[[3]]
sapply(x, typeof)
x[sapply(x, length) > 5]
x[sapply(x, is.numeric)]
sapply(x[sapply(x, is.numeric)], mean)
