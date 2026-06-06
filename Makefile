# ==========================================
#              MAKEFILE - MINISHELL
# ==========================================

# Variables
CC = gcc
CFLAGS = -Wall -g
SRC = minishell.c fonctions.c
OBJ = $(SRC:.c=.o)
NAME = minishell

# Règle par défaut 
all: $(NAME)

# Compilation de l'exécutable à partir des objets
$(NAME): $(OBJ)
	$(CC) -o $@ $^

# Compilation des fichiers .c en .o
%.o: %.c header.h fonctions.h
	$(CC) $(CFLAGS) -c $< -o $@
	
# Déclaration des cibles phony
.PHONY: all clean fclean re man

# Nettoyage des fichiers objets (.o)
clean:
	rm -f $(OBJ)

# Nettoyage complet : objets + exécutable
fclean: clean
	rm -f $(NAME)

# Recompilation complète (clean + build)
re: fclean all

# Raccourci pour l'exécution du man
man:
	man ./minishell.1


