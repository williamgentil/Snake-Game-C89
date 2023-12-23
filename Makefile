# Variables
ofiles = affichage.o apple.o game.o main.o snake.o
flags = -ansi -pedantic 

# Cibles
run: snake
	./snake

snake: ${ofiles}
	gcc ${flags} -o snake ${ofiles} -lgraph
	
affichage.o: snake.o apple.o
	gcc ${flags} -c affichage.c

apple.o: snake.o 
	gcc ${flags} -c apple.c

game.o: 
	gcc ${flags} -c game.c

main.o: ${ofiles}
	gcc ${flags} -c main.c

snake.o:
	gcc ${flags} -c snake.c

clean:
	rm snake
	rm ${ofiles}
