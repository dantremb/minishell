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


	echo = bool ft_echo(char *buffer);
	cd = bool ft_cd(char *buffer);
	pwd = bool ft_pwd(char *buffer);
	export = bool ft_export(char *buffer);
	unset = bool ft_unset(char *buffer);
	env = bool ft_env(void);
	$ = char *ft_get_variable(char *buffer);
	< = bool ft_redirect_input(char *buffer);
	> = bool ft_redirect_output(char *buffer);
	<< = bool ft_redirect_input_heredoc(char *buffer);
	>> = bool ft_redirect_output_append(char *buffer);