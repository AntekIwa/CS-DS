top <- c(" _ ","  ","  _ ", " _ ", "    ", "  _ ", "  _ ","  _ ","  _ ","  _ ")
mid <- c("| |"," |","  _|"," _|", " |_|", " |_ ", " |_ "," |",  " |_|"," |_|")
bot <- c("|_|"," |"," |_ ", " _|", "   |", "  _|", " |_|"," |",  " |_|","  _|")
x <- c(4,2,1)
cat(paste(top[x + 1], collapse = " "), "\n")
cat(paste(mid[x + 1], collapse = " "), "\n")
cat(paste(bot[x + 1], collapse = " "), "\n")

wypisz_kalkulator <- function(x) {
  idx <- x + 1
  
  cat(paste(top[idx], collapse = " "), "\n")
  cat(paste(mid[idx], collapse = " "), "\n")
  cat(paste(bot[idx], collapse = " "), "\n")
}

# Testujemy:
wypisz_kalkulator(c(4, 2, 1))
wypisz_kalkulator(c(2, 0, 2, 6))
