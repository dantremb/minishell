# minishell

- Afficher un prompt en l’attente d’une nouvelle commande.
- Posséder un historique fonctionnel.
- Gérer ’ (single quote) qui empêche le shell d’interpréter les 				 	méta-caractères entre guillemets.
- Gérer " (double quote) qui empêche le shell d’interpréter les 					méta-caractères entre guillemets sauf le $ (signe 	dollar).
- Chercher et lancer le bon exécutable (en se basant sur la variable 				d’environnement PATH, ou sur un chemin relatif ou absolu).
- "<" doit rediriger l’entrée.
- ">" doit rediriger la sortie.
- "<<" doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une 		ligne contenant le délimiteur. l’historique n’a pas à être mis à jour
- ">>" doit rediriger la sortie en mode append.
- Implémenter les pipes (caractère |).
- Gérer les variables d’environnement (un $ suivi d’une séquence de caractères) 	qui doivent être substituées par leur contenu.
- Gérer $? qui doit être substitué par le statut de sortie de la dernière 			pipeline exécutée au premier plan.
- Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
	- ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
	- ctrl-D quitte le shell.
	- ctrl-\ ne fait rien.
- Votre shell doit implémenter les builtins suivantes :
	- echo et l’option -n
	- cd uniquement avec un chemin relatif ou absolu
	- pwd sans aucune option
	- export sans aucune option
	- unset sans aucune option
	- env sans aucune option ni argument
	- exit sans aucune option

**Variable disponible pour chaque commande.**

	*next				pointer on next command.
	*prev;				pointer on last command.
	builtins;			NULL or name of builtins.
	**here_doc;			2D array with line returned from delemiter.
	**cmd;				2D array ready to send to execve.
	*path;				Path to command for execve.
	*input;				name of input file.
	*output;			name of output file.
	append_mode;		open output FD with append.
	*link_next;			| (only pipe if no bonus ?)
	**envp;				same as the one in env.struct ?.
	*queue_link;		pointer to environement structure.

	pid;				process ID of children doing the command.
	fd[2];				Tunnel between process.
	infile;				integer to store FD to use for OPEN, CLOSE and DUP2.
	outfile;			integer to store FD to use for OPEN, CLOSE and DUP2.
