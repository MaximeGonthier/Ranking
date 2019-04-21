################
### Makefile ###
################

CC = @gcc
CFLAGS = 
SUPPR = @rm -f
EXEC = ranking
FSRC = 
FHEAD = 
SRC = main.c ajoutsommetsattaquants.c ranking.c
OBJ = $(SRC: .c=.o)

all: $(EXEC)
	./$(EXEC)

compil: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^

ajoutsommetsattaquants.o: ajoutsommetsattaquants.c ajoutsommetsattaquants.h
	$(CC) -o $@ -c $< $(CFLAGS)

ranking.o: ranking.c ranking.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c ranking.h ajoutsommetsattaquants.h
	$(CC) -o $@ -c $< $(CFLAGS)


clean: 
	$(SUPPR) *.o
	$(SUPPR) $(EXEC)