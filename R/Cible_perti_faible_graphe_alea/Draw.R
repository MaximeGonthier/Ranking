# pour executer le code : R CMD BATCH "Draw.R"

Anneau_aleatoire = read.table("Anneau_alea.data")
#~ hist(Anneau_aleatoire[,1])

plot(density(Anneau_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,6.4284e-06,1.4494e-06),add=T,col="red")

# la fonction de répartition
curve(pnorm(x,6.4284e-06,1.4494e-06),from=4e-6,to=1.2e-5,col="red")


#~ hist(Anneau_aleatoire[,1], col = "lightblue")
qqnorm(Anneau_aleatoire[,1], col="blue")
hist(Anneau_aleatoire[,1], col = "lightblue", prob=T)
den <- density(Anneau_aleatoire[,1])
lines(den, col = "red")
#~ abline(v = moy, col = "black", lty ="dotted")
#~ curve(dnorm(x, moy, ecart), add=T, col="blue")

#~ pourcentage de valeur en 8 et 6
pnorm(lower.tail = 6e-06, upper.tail = 8e-06)
pnorm(6e-06)
#~ dnorm(c(5.0e-6,8.0e-6), 6.4284e-06,1.4494e-06)
