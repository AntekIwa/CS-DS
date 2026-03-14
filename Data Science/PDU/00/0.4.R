sin(0.67)

x <- seq(from = 0, to = 2 * pi, by = 0.01)
y <- sin(x)
plot(x, y, )
wsp_x <- cos(x)
wsp_y <- sin(x)
plot(wsp_x, wsp_y, asp = 1)
