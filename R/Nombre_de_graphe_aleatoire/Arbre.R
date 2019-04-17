# pour executer le code : R CMD BATCH "Draw.R"

Anneau_aleatoire = read.table("Arbre.data")

#~ hist(Anneau_aleatoire[,1])

plot(density(Anneau_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,1.74e-04,7.34697e-07),add=T,col="red")

