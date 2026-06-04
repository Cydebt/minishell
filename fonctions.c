#include "fonctions.h"


//fonction découper
int decouper(char * ligne, char * separ, char * mot[], int maxmot) {
    int i;

    mot[0] = strtok( ligne, separ);
    for( i = 1; mot[i - 1] != 0; i ++) {
        if ( i == maxmot) {
            fprintf ( stderr, "Erreur dans la fonction decouper: trop de mots\n");
            mot[i - 1] = 0;
            break;
        }
        mot[i] = strtok( NULL, separ);
    }
    return i;
}

// Fonction redirection
void redirection(char * argv[], int ac) {
    int i;
    int dupOK;
    int fd;

    for (i = 0; i < ac; i++) {
        if (argv[i] == NULL) continue;

        if (strcmp(argv[i], ">") == 0) { // on cherche le caractère > avec strcmp
            fd = open(argv[i + 1], O_WRONLY | O_CREAT, 0666); // Si le fichier n'existe pas, on le crée
            if (fd < 0) { // gestion des erreurs d'ouverture du fichier
                perror("Erreur d'ouverture du fichier");
                exit(1);
            }
            dupOK = dup2(fd, 1); // on utilise dup2 pour débrancher la sortie 1 et brancher sur fd
            if (dupOK < 0) {
                perror("Erreur lors du changement de sortie (dup2)"); // gestion des erreurs
                exit(1);
            }
            argv[i] = NULL; // on enlève le > et le fichier de redirection avant de faire un execvp
            argv[i + 1] = NULL;
            close(fd);
        } 
        else if (strcmp(argv[i], "<") == 0) { // on cherche le caractère <
            fd = open(argv[i + 1], O_RDONLY);
            if (fd < 0) { // gestion des erreurs d'ouverture du fichier
                perror("Erreur d'ouverture du fichier");
                exit(1);
            }
            dupOK = dup2(fd, 0); // on utilise dup2 pour débrancher l'entrée 0 et brancher sur fd
            if (dupOK < 0) {
                perror("Erreur lors du changement de sortie (dup2)"); // gestion des erreurs
                exit(1);
            }
            argv[i] = NULL; // on enlève le < et le fichier de redirection avant de faire un execvp
            argv[i + 1] = NULL;
            close(fd);
        }
    }
}

//Fonction moncd
void moncd(char ** mot) {// pour comparer des chaines
                
            char * dir;
            int t;

             if (mot[2]) { //si 2 arguments ou + pour moncd
            fprintf ( stderr, "usage: %s [dir]\n", mot[0]) ;
            return;
            } 
            else if (mot[1]==NULL) {
                dir = getenv("HOME");
                if (dir ==0)
                dir ="/tmp"; //chemin par défaut
                
            }
            else
            dir = mot[1];
            t = chdir(dir);
            if (t<0) {
                perror(dir);
            }
        }