/* ************************************************************************** */
/* NOM DU SCRIPT : monshell.c                                                 */
/* ROLE          : Mini-shell capable d'exécuter des commandes avec des pipes         */
/* AUTEUR        : Cyril DEBRABANT  + cours de Mr.Kislin        */    
/* VERSION       : 3.0 (Intégration pipes)                       */
/* LICENCE       : Système - L2                                               */
/* PRÉALABLE     : Nécessite un compilateur C (gcc)                           */
/* USAGE         : ./monshell                                                 */
/* EXEMPLE       : ? ls -l                                                    */
/* ? ./monshell ls -l | grep monshell                                              */
/* ************************************************************************** */



#include "header.h"

#define PROMPT "? "

//prototype
int decouper(char *, char *, char **, int );

int main(int argc, char * argv[]) {
    char ligne[ MaxLigne];
    char pathname[MaxPathLength];
    char * mot[MaxMot];
    char * dirs[ MaxDirs];
    int i, tmp;
    char * commandes[MaxCommandes]; //pour découper les diff commandes avant et après |
    int nbcommandes_pipes; //correspond au nombres de commandes sur la ligne si il y a pipes
    int pipes[2]; // tableau avec les pipes
    int fd_in = 0; //mémoire de stdin précédent

    decouper(strdup(getenv("PATH")), ":", dirs, MaxDirs);
    
    /* On rempli le tableau commandes avec les commandes avant  et après les | */
    
   


    /* Lire et traiter chaque ligne de commande */
    for( printf(PROMPT); fgets(ligne, sizeof ligne, stdin) != 0; printf( PROMPT) ) {

        nbcommandes_pipes = decouper(ligne, "|", commandes, MaxMot) -1 ;  // On fait -1 l'indice renvoyé par la fonction découper fait un tour de +

        if (commandes[0] == 0)
            // ligne vide
            continue;

        fd_in = 0; //on réinitialise fd_in à 0 à chaque retour au prompt

        for (int c =0; c < nbcommandes_pipes ; c++) {
            decouper(commandes[c], " \t\n", mot, MaxCommandes);
            if (mot[0] == 0)
            // ligne vide
            continue;
            
             
            if (c < nbcommandes_pipes - 1) {
                if (pipe(pipes) < 0) { //création des pipes dans "pipes" et gestion des erreurs en mm temps
                    perror("Erreur pipe");
                    break;
                }
            }

            tmp = fork();

            if ( tmp < 0) { //erreur de fork
            perror("fork");
            continue;
            }

            if (tmp == 0) {//processus enfant

                if (fd_in != 0) { //si c'est pas le premier processus enfant, 
                    dup2(fd_in, 0); // Dans ce cas là on branche fd_in sur l'entrée
                    close(fd_in);   // On ferme l'entrée pipe
                }
            

                 if (c < nbcommandes_pipes - 1) { //si on est pas au dernier processus enfant
                    dup2(pipes[1], 1); // On change la sortie 
                    close(pipes[0]);   // Pas besoin de pipes 0,  on ferme
                    close(pipes[1]);   // On ferme pipes 1
                }

                for( i = 0; dirs[i] != 0; i ++) {
                snprintf( pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
                execv(pathname, mot);
                }

                // aucun exec n'a fonctionne
                fprintf ( stderr, "%s: not found\n", mot[0]);
                exit (1);
            }

            if (tmp > 0) { //processus parent
                if (fd_in != 0) close(fd_in);
                if (c < nbcommandes_pipes - 1) {
                close(pipes[1]); // Le parent n'écrit jamais
                fd_in = pipes[0]; // Le parent garde la sortie pour la donner au suivant
                 }
                } 
        }
        
        while (wait(NULL) > 0);
    }
    printf( "Bye\n");
    return 0;
}

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