# pour executer le code : R CMD BATCH "Draw.R"

Anneau_aleatoire = read.table("Anneau.data")

#~ hist(Anneau_aleatoire[,1])

plot(density(Anneau_aleatoire[,1]))
# courbe a partir de v
 curve(dnorm(x,1.72e-04,5.75759e-07),add=T,col="red")

