#ifndef HEADER_H
#define HEADER_H



# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <assert.h>
#include <string.h>

enum {
    MaxLigne = 1024,       // longueur max d'une ligne de commandes
    MaxMot = MaxLigne / 2, // nbre max de mot dans la ligne
    MaxDirs = 100,         // nbre max de repertoire dans PATH
    MaxPathLength = 512,   // longueur max d'un nom de fichier
    MaxCommandes = 100, // Nombre max de commandes sur une ligne (avec les |)
};

#define PROMPT "? "



#endif