# minishell

- Show a prompt waiting for a new command.
- History management.
- Single quote avoid all the special characters.
- Double quote avoid all the special characters except `$`.
- Launch executable with their absolute or relative path.
- "<" redirect input.
- ">" redirect output.
- "<<" open here document.
- ">>" redirect output with append mode.
- "|" implement pipe.
- "$" implement environment variable.
- "$?" implement the last return code.
- ctrl-C show new prompt.
- ctrl-D exit minishell.
- ctrl-\ do nothing.
- echo with -n
- cd only with a relative or absolute path.
- pwd with no options.
- export with no options.
- unset with no options.
- env with no options.
- exit  with no options.

# Test to do

<<end cat
<< end cat
<infile cat
< infile cat
echo test >>outfile
echo test >> outfile
echo test > outfile
echo test >outfile

<<end cat | << end cat | <infile cat | < infile cat | echo test > outfile | echo test >outfile | echo test >> outfile | echo test >>outfile

## Defense ##

- avec un Path absolu comme /bin/ls et d'autre path relatif
- une commande vide
- une commande avec des espaces et tabulations
- echo avec et sans arguments
- echo avec l'option -n
- exit avec et sans arguments
- env affiche les variables d'environnement
- exportez des variables et véfifier si elle sont remplacé si déjà existante
- cd avec des chemins existant et non existant.
- cd avec . et ..
- pwd avec et sans arguments
- executez des commandes avec des chemin relatif avec beaucoup de ../
- executez des commandes sans la variable PATH
- vérifier que les PATH sont bien analysé de gauche a droite dans ft_get_path
- executez des commandes avec des redirections < << > >> (heredoc n'est pas obliger de mettre a jour l'historique)
- executez des commandes avec des pipes, avec des commandes valide et invalide entre 2 pipes
- entrer une commande, appuyez sur ctrl-C, appuyez sur entrée, le buffer devrait être vide et ne devrait rien executer
- naviger dans l'historique avec les flèches du haut et du bas
- vérifier des commandes qui ne fonctionne pas
- cat | cat | ls doit fonctionner
- essayer des longues commandes avec des tonnes d'arguments. Amusez-vous
- executez echo avec des variables d'environnement ($variable)
- single quote ne va pas expand les variables et les double quote oui
- valeur de retour des processus avec $?
- ctrl-c ctrl-\ ctrl-d
- executez des commandes avec singles quotes qui ne devrait pas expand les variables et metacaractères