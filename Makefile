# Variables
ofiles = affichage.o apple.o game.o main.o snake.o obstacle.o
fonctions = affichage.o apple.o game.o snake.o obstacle.o
flags = -ansi -pedantic 

# BUTS
run: snake
	./snake

snake: ${ofiles}
	gcc ${flags} -o snake ${ofiles} -lgraph
	
affichage.o: snake.o apple.o
	gcc ${flags} -c affichage.c

apple.o: snake.o 
	gcc ${flags} -c apple.c

obstacle.o:
	gcc $(flags) -c obstacle.c

game.o: 
	gcc ${flags} -c game.c

main.o: ${fonctions}
	gcc ${flags} -c main.c

snake.o:
	gcc ${flags} -c snake.c

clean:
	rm ${ofiles}
	rm snake
	
