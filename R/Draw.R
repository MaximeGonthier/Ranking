# pour executer le code : R CMD BATCH "Draw.R"

modelname = read.table("Arbre_alea.data")
hist(modelname[,1])


#~ x <- rnorm(30,7.5395e-06,4.3076e-21)
#~ y <- rnorm(1000,3,1)
#~ z <- c(x,y)
#~ r <- c(5.0e-22,9.0e-06)
#~ hist(z,freq=FALSE,col=0,ylim=c(0,0.5),20)
#~ plot(function(x) 0.5*dnorm(x,0,0.5),xlim=r,col=2,add=TRUE)
#~ plot(function(x) 0.5*dnorm(x,3,1),xlim=r,col=3,add=TRUE)

#~ smp <- read.csv2("Graphe_alea.csv")
#~ hist(smp)
