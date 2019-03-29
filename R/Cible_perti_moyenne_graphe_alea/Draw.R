# pour executer le code : R CMD BATCH "Draw.R"

Arbre_aleatoire = read.table("Arbre_alea.data")
#~ hist(Arbre_aleatoire[,1])

plot(density(Arbre_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,2.5412e-05,1.3384e-06),add=T,col="red")

# la fonction de répartition
curve(pnorm(x,2.5412e-05,1.3384e-06),from=2.0e-05,to=3.0e-5,col="red")


#~ hist(Arbre_aleatoire[,1], col = "lightblue")
qqnorm(Arbre_aleatoire[,1], col="blue")
hist(Arbre_aleatoire[,1], col = "lightblue", prob=T)
den <- density(Arbre_aleatoire[,1])
lines(den, col = "red")
abline(v = moy, col = "black", lty ="dotted")
curve(dnorm(x, moy, ecart), add=T, col="blue")
