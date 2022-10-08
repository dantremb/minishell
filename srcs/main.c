/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:49:16 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/30 22:56:22 by dantremb         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int error_status;

// print le tableau de commandes pour debug
void	ft_print_table(shell_t *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->nb_cmd)
	{
		j = 0;
		ft_color(1);
		dprintf(2, "------------ TOKEN -----------------\n");
		ft_color(6);
		dprintf(2, "cmd %d = \t", i);
		while (shell->cmd[i].token[j])
		{
			ft_color(3);
			dprintf(2, "[\033[1;34m%s\033[1;33m]", shell->cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
		dprintf(2, "------------------------------------\n");
	ft_color(8);
}

// free all the allocated memory
void	ft_free(shell_t *shell, int flag)
{
	int	i;

	if (flag == 1){
		free(shell);
	}
	if (flag == 2){
		ft_free_array(shell->env);
		free(shell);
	}
	if (flag == 3){
		free(shell->buffer);
		ft_free_array(shell->env);
		free(shell);
	}
	if (flag == 4){
		free(shell->cmd);
		free(shell->buffer);
		ft_free_array(shell->env);
		free(shell);
	}
	if (flag == 5){
		free(shell->pid);
		free(shell->cmd);
		free(shell->buffer);
		ft_free_array(shell->env);
		free(shell);
	}
	if (flag == 6){
		i = -1;
		while (++i < shell->nb_cmd)
			free(shell->cmd[i].token);
		free(shell->pid);
		free(shell->cmd);
	}
	if (flag == 7){
		i = -1;
		while (++i < shell->nb_cmd)
			free(shell->cmd[i].token);
		free(shell->pid);
		free(shell->cmd);
		free(shell->buffer);
		ft_free_array(shell->env);
		free(shell);
	}
}

// print le message sur le FD 2
// free les elements malloc
// exit avec le status de la derniere commande
void	ft_exit(shell_t *shell, char *msg, int status, int flag)
{
	ft_putstr_fd(msg, 2);
	ft_free(shell, flag);
	exit(status);
}

// cherche dans la variable d'environnement une ligne avec le buffer
// avant le = et retourne un pointer sur le premier caractere apres le =
char	*ft_get_variable(shell_t *shell, char *buffer, int flag)
{
	int		i;

	i = -1;
	if (!buffer)
		return (NULL);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (shell->env[i][ft_strlen(buffer)] == '=')
				return (shell->env[i] + (ft_strlen(buffer) + 1));
		}
	}
	if (flag == 1)
		buffer[0] = '\0';
	return (buffer);
}

// si le flag est a 0 on print les variables d'environnement + ceux cachés
// si le flag est a 1 on print les variables avec un = seulement
void	ft_env(shell_t *shell, int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (shell->env[++i])
			printf("[%d]%s\n", i, shell->env[i]);
	}
	else
	{
		while (shell->env[++i])
		{
			if (shell->env[i][0] != '<' && shell->env[i][1] != '-' && ft_strchr(shell->env[i], '='))
				printf("%s\n", shell->env[i]);
		}
	}
}

// cherche dans la variable d'environnement une ligne avec le buffer
// et si il est suivi d'un "=" on free le pointer et on déplace les autres
// pointeurs du tableau vers le bas puis assigne le dernier pointeur a NULL
void	ft_unset(shell_t *shell, char *buffer)
{
	int	i;

	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], buffer, ft_strlen(buffer)) == 0
			&& shell->env[i][ft_strlen(buffer)] == '=')
		{
			free(shell->env[i]);
			while (shell->env[i + 1])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			shell->env[i] = NULL;
		}
	}
}

// si aucun argument on imprime les variables d'environnement
// si le premier argument provenant de l'utilisateur n'est pas aplhabétique on retourne une erreur
// si l'argument contien un "=" on regarde si elle existe et unset
// on remalloc l'environement de 1 de plus
// on ajoute une copie de l'argument a la fin de l'environement
void	ft_export(shell_t *shell, char *arg, int flag)
{
	char	*duplicate;

	if (!arg)
		ft_env(shell, 0);
	else if (arg && ft_isalpha(arg[0]) == 0 && flag == 1)
		printf("-bash: export: `%s': not a valid identifier\n", arg);
	else
	{
		if (ft_strchr(arg, '='))
		{
			duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
			if (ft_get_variable(shell, duplicate, 0))
				ft_unset(shell, duplicate);
			free (duplicate);
		}
		shell->env = ft_remalloc(shell->env, 1, 1);
		shell->env[ft_array_size(shell->env) - 1] = ft_strdup(arg);
	}
}

//si le buffer est un dossier valide à l'aide de chdir qui change le dossier courant
// on unset le oldpwd courant
// on construit le nouveau oldpwd avec le pwd courant et export dans l'environement
// on unset le pwd courant
// on construit le nouveau pwd avec le buffer et export dans l'environement
void	ft_cd(shell_t *shell, char *buffer)
{
	char	*temp[2];
	
	if (buffer && chdir(buffer) == 0)
	{
		ft_unset(shell, "OLDPWD");
		temp[0] = ft_get_variable(shell, "PWD", 0);
		temp[1] = ft_strjoin("OLDPWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		free(temp[1]);
		ft_unset(shell, "PWD");
		temp[0] = getcwd(NULL, 0);
		temp[1] = ft_strjoin("PWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		free(temp[0]);
		free(temp[1]);
	}
	else
		printf("cd: %s: No such file or directory\n", buffer);
}

// Si le premier token est <-n> on donne la valeur 1 au Flag
// si le token contien que des espaces on passe au token suivant et print un espace
// sinon on print le token et un espace sauf pour le dernier token
// si le flag est a 0 on print le retour a la ligne
void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (arg[1] && !ft_is_only(&arg[1][1], 'n') == 0)
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (ft_is_only(arg[i], ' '))
			i++;
		else
		{
			printf("%s", arg[i++]);
			if (arg[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

// on regarde si la commande est deja un path
// si oui on retourne le path
// si non on ajoute un / devant la commande
// on va chercher la ligne contenant les paths et split avec les <:>
// on ajoute le path avec la commande path/<commande>
// on regarde si le programme existe avec access
// si oui on retourne le path
// si non on free le path et on continue
char	*ft_get_path(shell_t *shell, int nb)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	char 	*test_path;
	int		i;
	i = -1;
	if (access(shell->cmd[nb].token[0], F_OK | X_OK) == 0)
		return (shell->cmd[nb].token[0]);
	program = ft_strjoin("/", shell->cmd[nb].token[0], 0);
	env_path = ft_get_variable(shell, "PATH", 0);
	fcnt_path = ft_split(env_path, ':');
	if (program == NULL || env_path[0] == '\0' || fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[++i])
	{
		test_path = ft_strjoin(fcnt_path[i], program, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		test_path = NULL;
	}
	ft_free_array(fcnt_path);
	free(program);
	return (test_path);
}

// trouve le chemin du programme
// si le chemin est trouvé on execute le programme
// sinon on affiche un message d'erreur et quitte le child
void	ft_execve(shell_t *shell, int nb)
{
	char	*cmd_path;
	
	cmd_path = ft_get_path(shell, nb);
	if (cmd_path != NULL)
		execve(cmd_path, shell->cmd[nb].token, shell->env);
	dprintf(2, "%s: command not found\n", shell->cmd[nb].token[0]);
	exit(127);
}

// on regarde si la commande est un builtin et l'éxecute
bool	ft_execute_builtin(shell_t *shell, int nb)
{
	if (ft_strncmp(shell->cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(shell->cmd[nb].token);
	else if (ft_strncmp(shell->cmd[nb].token[0], "env", 3) == 0)
		ft_env(shell, 1);
	else if (ft_strncmp(shell->cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(shell, shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable(shell, "PWD", 0));
	else if (ft_strncmp(shell->cmd[nb].token[0], "export", 6) == 0)
		ft_export(shell, shell->cmd[nb].token[1], 1);
	else if (ft_strncmp(shell->cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(shell, shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "exit\0", 5) == 0)
		ft_exit(shell, "Goodbye\n", 0, 7);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(shell_t *shell, int nb)
{
	int	fd[2];
	
	if(pipe(fd) == -1)
		ft_exit(shell, "pipe error\n", 14, 7);
	shell->pid[nb] = fork();
	if (shell->pid[nb] == 0)
	{
		if (nb < shell->nb_cmd - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		if (ft_execute_builtin(shell, nb) == false)
			ft_execve(shell, nb);
		else
			exit(0);
	}
	else if (nb < shell->nb_cmd - 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

// on crée un child pour executer toutes les commandes
// a l'intérieur du child on relance un child pour chaque commande
// on attend la fin de chaque child puis retourne le dernier status
// on quitte le child du subshell et retourne le status
int	ft_subshell(shell_t *shell, int nb)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		while (nb < shell->nb_cmd) 
			ft_exec_cmd(shell, nb++);
		nb = 0;
		while (nb < shell->nb_cmd)
			waitpid(shell->pid[nb++], &status, 0);
		exit (status);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (status);
}

// on execute le builtin si possible
// sinon on execute le programme dans un child
// on attend la fin de l'execution du child
// on retourne le status de la commande
int	ft_execute_solo(shell_t *shell, int nb)
{
	int	status;
	
	//ft_clean_token(shell->cmd[nb].token);
	if (ft_execute_builtin(shell, nb) == false)
	{
		shell->pid[nb] = fork();
		if (shell->pid[nb] == 0)
			ft_execve(shell, nb);
		else
			waitpid(shell->pid[nb], &status, 0);
	}
	return (status);
}

// on sauvegarde le FD de stdin et stdout
// on lance le subshell si plusieurs commandes
// sinon on execute la commande solo
// on récupère le status de la derniere commande
// on restore le FD de stdin et stdout
void	ft_execute_cmd(shell_t *shell, int nb)
{
	int old_stdin;
	int old_stdout;
	int	status;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (shell->nb_cmd > 1) {
		status = ft_subshell(shell, nb);
	}
	else {
		status = ft_execute_solo(shell, nb);
	}
	error_status = status;
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
}

// on skip les espaces et tabulations
// si le premier caractere set <$> et le suivant est <?>
// on imprime le status de la derniere commande
int	ft_status(shell_t *shell)
{
	int	i;

	i = 0;
	while (shell->buffer[i] && (shell->buffer[i] == ' ' || shell->buffer[i] == '\t'))
		i++;
	if (shell->buffer[i] == '$' && shell->buffer[i + 1] == '?')
	{
		printf("%d: command not found\n", error_status);
		error_status = 0;
		return (1);
	}
	return (0);
}

// on avance dans le buffer
// on incremente <d> ou <s> a chaque simple ou double quote
// si la division en 2 d'une des deux variables de laisse pas de reste
// alors on a un nombre impair de quote d'une des 2 types
int	ft_check_closed_quote(char *buf)
{
	int	i;
	int	d;
	int	s;

	i = -1;
	d = 0;
	s = 0;
	while (buf[++i]){
		if (buf[i] == '\"')
			d++;
		if (buf[i] == '\'')
			s++;
	}
	if ((d && (d % 2) != 0) || (s && (s % 2)) != 0){
		printf("Error Quote not closed\n");
		return (0);
	}
	return (1);
}

int	ft_pipe_count(shell_t *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (shell->buffer[i])
	{	
		if (shell->buffer[i] == '|')
		{
			if (shell->buffer[i + 1] == '|')
			{
				shell->buffer[i] = '\0';
				shell->nb_cmd = count;
				return (0);
			}
			count++;
		}
		i++;
	}
	shell->nb_cmd = count;
	return (0);
}

//pour chaque commande on va compter le nombre de token
//on va allouer la memoire pour le tableau de token
//on va remplir le tableau de token avec strtok
void	ft_parse_token(shell_t *shell)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < shell->nb_cmd)
	{
		count = ft_token_count(shell->cmd[c].buffer, ' ');
		shell->cmd[c].token = ft_calloc(sizeof(char *), count + 2);
		if (!shell->cmd[c].token)
			ft_exit(shell, "Error: malloc failed\n", 15, 5);
		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		//ft_parse_heredoc(shell->cmd[c].token);
	}
}

// on check si le buffer contient des quotes non fermées
// on regarde si la commande $? est presente et l'éxecute
// on compte le nombre de commandes et calloc le tableau de cmd
// on split le buffer en petit buffer pour chaque commande
int 	ft_parse(shell_t *shell)
{
	int i;

	i = 0;
	if (ft_check_closed_quote(shell->buffer) == 0 || ft_status(shell) 
		|| ft_pipe_count(shell))
		return (0);
	shell->cmd = ft_calloc(sizeof(shell_t), shell->nb_cmd);
	if (shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15, 3);
	shell->pid = ft_calloc(sizeof(int), shell->nb_cmd);
	if (shell->pid == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15, 4);
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_parse_token(shell);
	return (1);
}

// on read sur le 0 avec Readline
// si le buffer est NULL (ctrl + D) on quitte la boucle
// si le buffer contient que des espaces on read sur le 0 a nouveau
// on ajoute l'historique
// on parse le buffer
// si valide on execute la commande
// on free le buffer
// on read sur le 0 a nouveau
int	ft_getprompt(shell_t *shell)
{
	shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (shell->buffer != NULL)
	{
		if (!ft_is_only(shell->buffer, ' '))
		{
			add_history(shell->buffer);
			if (ft_parse(shell)){
				ft_execute_cmd(shell, 0);
				ft_free(shell, 6);
			}
		}
		free(shell->buffer);
		shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
	return (0);
}

//sur CTRL + C on print un retour a la ligne
//on se deplace sur une nouvelle ligne
//on efface la ligne
//on affiche le prompt
//on set le error status a 130
void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		error_status = 130;
	}
}

// Set le error status a 0
// calloc de la structure principal
// copie de la variable environ dans la structure
shell_t	*ft_init_minishell(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	shell_t *shell;

	error_status = 0;
	shell = ft_calloc(1, sizeof(shell_t));
	if (!shell)
		ft_exit(shell, "Error: malloc failed\n", 15, 0);
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL){
		ft_exit(shell, "Error: malloc failed\n", 15, 1);
	}
	return (shell);
}

// Main function
int	main(int ac, char **av, char **env)
{
	shell_t *shell;
	
	shell = ft_init_minishell(ac, av, env);
	signal(SIGINT, ft_signal);
	ft_getprompt(shell);
	ft_exit(shell, "Goodbye\n", 0, 2);
}
