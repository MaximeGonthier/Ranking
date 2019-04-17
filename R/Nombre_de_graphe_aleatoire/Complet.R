# pour executer le code : R CMD BATCH "Draw.R"

Anneau_aleatoire = read.table("Complet.data")

#~ hist(Anneau_aleatoire[,1])

plot(density(Anneau_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,1.15e-04,4.06743e-06),add=T,col="red")

