__________________________________________________________________________

Contact : Cydebt@protonmail.me

FRENCH : 

Minishell en C

Développement d'un interpréteur de commandes interactif (Shell) personnalisé en C.

Le projet est structuré de manière modulaire :
- 'minishell.c' : Point d'entrée de l'application et boucle principale (Prompt, lecture, exécution).
- 'header.h' : Déclarations des structures globales et prototypes des fonctions.
- 'fonctions.c' / 'fonctions.h' : Implémentation des outils de parsing (découpage de la ligne de commande) et de la logique système.

Fonctionnalités :

- Commnades externes : Exécution de toutes les commandes système standards via la recherche dynamique dans les répertoires du `PATH` (gestion des processus enfants avec `fork` et `execv`).
- Commandes internes : Gestion native de 'moncd' (navigation dans les répertoires) et 'monexit' (fermeture propre du shell).
- Redirections d'entrées/sorties : Support des opérateurs < (redirection d'entrée) et > (redirection de sortie avec écrasement du fichier de destination).
- Pipes : Gestion de l'enchaînement de commandes via l'opérateur | (redirection des flux standard de sortie d'une commande vers l'entrée de la suivante).
- Processus en arrière plan : Support du symbole & pour lancer des tâches en tâche de fond sans bloquer le prompt principal, incluant la gestion et le nettoyage propre des processus zombies via l'appel système `waitpid` avec l'option `WNOHANG`.

Compilation/exécutions :

Pour compiler le projet proprement avec les flags de sécurité :
Sur Bash :

gcc -Wall -Wextra minishell.c fonctions.c -o minishell
________________________________________________________________________________

ENGLISH :

Minishell in C

Development of a custom interactive command interpreter (Shell) in C.

The project is structured modularly:

- 'minishell.c': Application entry point and main loop (Prompt, read, execute).
- 'header.h': Declarations of global structures and function prototypes.
- 'functions.c' / 'functions.h': Implementation of parsing tools (command line slicing) and system logic.

Features:
- External Commands: Execution of all standard system commands via dynamic search in the `PATH` directories (child process management with `fork` and `execv`).
- Internal Commands: Native support for 'mycd' (directory navigation) and 'myexit' (clean shell shutdown).
- Input/Output Redirections: Support for the < (input redirection) and > (output redirection with overwriting of the destination file) operators.
- Pipes: Command chaining management via the | operator (redirection of standard output streams from one command to the input of the next).
- Background Processes: Support for the & symbol to launch background tasks without blocking the main prompt, including the management and clean cleanup of zombie processes via the `waitpid` system call with the `WNOHANG` option.

Compilation/Execution:

To compile the project cleanly with security flags:
On Bash:

gcc -Wall -Wextra minishell.c functions.c -o minishell
________________________________________________________________________________
