idx_losowe <- sample(x = nrow(iris), size = 100)
idx_losowe
iris_losowe100 <- iris[idx_losowe,]
iris_losowe100


rozmiar <- round(0.05*nrow(iris))
rozmiar
idx_5 <- sample(x = nrow(iris), size = rozmiar)
iris_5pro <- iris[idx_5, ]
iris_5pro


iris_pierwsze100 <- iris[1:100,]
iris_pierwsze100

iris_ostatnie_100 <- tail(iris, n = 100)
iris_ostatnie_100
