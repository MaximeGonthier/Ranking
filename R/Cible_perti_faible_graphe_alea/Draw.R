# pour executer le code : R CMD BATCH "Draw.R"

Complet_aleatoire = read.table("Complet_alea.data")
#~ hist(Complet_aleatoire[,1])

plot(density(Complet_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,2.5412e-05,1.3384e-06),add=T,col="red")
# courbe théorique :
curve(dnorm(x,0,1),col="green",lty=2,add=T)

# ou tout simplement si tu ne veux que la fonction de densité :
curve(dnorm(x,0,1),col="red",from=-4,to=4)

# la fonction de répartition
curve(pnorm(x,0,1),from=-4,to=4,col="red")


hist(Complet_aleatoire[,1], col = "lightblue")
qqnorm(Complet_aleatoire[,1], col="blue")
hist(Complet_aleatoire[,1], col = "lightblue", prob=T)
den <- density(Complet_aleatoire[,1])
lines(den, col = "red")
abline(v = moy, col = "black", lty ="dotted")
curve(dnorm(x, moy, ecart), add=T, col="blue")
