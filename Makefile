CC=gcc
CFLAGS=-Wall -g
LIBS=-lgraph

# Liste des fichiers sources
SRCS=main.c snake.c apple.c obstacle.c graphics.c utils.c

# Liste des fichiers objets à générer
OBJS=$(SRCS:.c=.o)

# Nom de l'exécutable
EXE=snake

# Règles de compilation pour chaque fichier objet
%.o: %.c
    $(CC) $(CFLAGS) -c $<


# Règle principale pour générer l'exécutable
$(EXE): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
    rm -f $(OBJS) $(EXE)

# Déclaration de la règle clean comme but factice
.PHONY: clean
