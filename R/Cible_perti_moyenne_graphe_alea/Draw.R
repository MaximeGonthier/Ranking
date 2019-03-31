# pour executer le code : R CMD BATCH "Draw.R"

Complet_aleatoire = read.table("Complet_alea.data")
#~ hist(Complet_aleatoire[,1])

plot(density(Complet_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,9.6176e-06,8.2171e-07),add=T,col="red")

# la fonction de répartition
curve(pnorm(x,9.6176e-06,8.2171e-07),from=8e-6,to=1.2e-5,col="red")


#~ hist(Complet_aleatoire[,1], col = "lightblue")
qqnorm(Complet_aleatoire[,1], col="blue")
hist(Complet_aleatoire[,1], col = "lightblue", prob=T)
den <- density(Complet_aleatoire[,1])
lines(den, col = "red")
abline(v = moy, col = "black", lty ="dotted")
curve(dnorm(x, moy, ecart), add=T, col="blue")

