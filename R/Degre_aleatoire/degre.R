# pour executer le code : R CMD BATCH "Draw.R"

modelname = "degre.data"
data = read.table(modelname)
attach(data);

Pertinence = V1
Degre = V2

plot(Degre,Pertinence,type="l",xlab="Degre",ylab="Pertinence",col="green")
