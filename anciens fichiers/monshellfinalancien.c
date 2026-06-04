/* ************************************************************************** */
/* NOM DU SCRIPT : monshell_2_1.c                                                 */
/* ROLE          : Mini-shell capable d'exécuter des commandes externes et    */
/* des commandes internes +des redirections(moncd, monexit).                   */
/* AUTEUR        : Cyril DEBRABANT  + cours de Mr.Kislin        */    
/* VERSION       :3.1 (Intégration de la modularité)                */
/* LICENCE       : Système - L2                                               */
/* PRÉALABLE     : Nécessite un compilateur C (gcc)                           */
/* USAGE         : gcc monshellfinal.c fonctions.c -o monshellfinal puis ./monshellfinal                                                 */
/* EXEMPLE       : ? ls -l                                                    */
/* ? moncd /tmp                                               */
/* ? monexit 
/* ? ls -l > liste.txt                                   */
/*TODO PROCEDURES EN ARRIERE PLAN ET PIPES*/
/* ************************************************************************** */




#include "fonctions.h"


int main(int argc, char * argv[]) {
    char ligne[ MaxLigne];
    char pathname[MaxPathLength];
    char * mot[MaxMot];
    char * dirs[ MaxDirs];
    int i, tmp;
    

    /* Decouper UNE COPIE de PATH en repertoires */
    decouper(strdup(getenv("PATH")), ":", dirs, MaxDirs);

    /* Lire et traiter chaque ligne de commande */
    for( printf( PROMPT); fgets(ligne, sizeof ligne, stdin) != 0; printf( PROMPT) ) {
    int MaxiMots = decouper(ligne, " \t\n", mot, MaxMot);
        
        if ( mot[0] == 0)
            // ligne vide
            continue;
//------------------Commande interne moncd --------------------------
        if (strcmp(mot[0],"moncd") == 0)  {// pour comparer des chaines
                //TODO ici faire un raccourci avec moncd()
            char * dir;
            int t;

             if (mot[2]) { //si 2 arguments ou + pour moncd
            fprintf ( stderr, "usage: %s [dir]\n", mot[0]) ;
            continue;
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
            continue;
            }
//--------------------------Fin de la commande  moncd-------------------------
//--------------------------Commande monexit------------------------------
        if (strcmp(mot[0],"monexit") == 0) {
            //TODO racourci monexit à faire
            printf("Je sors du minishell.\n"); //pour vérifier
            exit(0);//code d'erreur OK
        }
//-------------------------Fin de la commande monexit----------------------
            tmp = fork();
        if ( tmp < 0) {
            perror("fork");
            continue;
        }
        
        // lancer le processus enfant
        if ( tmp != 0) {
            while(wait(0) != tmp)
                ; // parent : attendre la fin de l ' enfant
            continue;
        }

        // enfant : exec du programme
        redirection(mot, MaxiMots); //on ajoute la prise en compte des < et >

        for( i = 0; dirs[ i ] != 0; i ++) {
            snprintf( pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
            execv(pathname, mot);
        }
        
        // aucun exec n'a fonctionne
        fprintf ( stderr, "%s: not found\n", mot[0]);
        exit (1);
    }
    
    printf( "Bye\n");
    return 0;
}



