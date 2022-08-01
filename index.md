![Book logo](docs/assets/images/top.png)

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

You can use the [editor on GitHub](https://github.com/dantremb/minishell/edit/gh-pages/index.md) to edit this page.
