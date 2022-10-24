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
	//printf("while i < %d\n", shell->nb_cmd);
	while (i < shell->nb_cmd)
	{
		j = 0;
		ft_color(1);
		dprintf(2, "------------ TOKEN -----------------\n");
		ft_color(6);
		dprintf(2, "cmd %d = \t", i);
		while (shell->cmd[i].token && shell->cmd[i].token[j])
		{
			ft_color(3);
			dprintf(2, "[\033[1;34m%s\033[1;33m]", shell->cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
		dprintf(2, "------------------------------------\n");
	ft_color(7);
}

// free all the allocated memory for the last command
void	ft_clear_command(shell_t *shell)
{
	int	i;
	i = -1;
	while (++i < shell->nb_cmd)
		ft_free(shell->cmd[i].save);
	shell->pid = ft_free(shell->pid);
	shell->cmd = ft_free(shell->cmd);
	shell->buffer = ft_free(shell->buffer);
	shell->nb_cmd = 0;
}

// print le message sur le FD 2
// free les elements malloc
// exit avec le status de la derniere commande
void	ft_exit(shell_t *shell, char *msg, int status)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	ft_free_array(shell->env);
	shell = ft_free(shell);
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
			ft_free(shell->env[i]);
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
			ft_free (duplicate);
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
		ft_free(temp[1]);
		ft_unset(shell, "PWD");
		temp[0] = getcwd(NULL, 0);
		temp[1] = ft_strjoin("PWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		ft_free(temp[0]);
		ft_free(temp[1]);
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
	i = 0;

	if (arg[1] && !ft_is_only(&arg[1][1], 'n' && ++i) == 0)
		flag = 1;
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

// on créé le nouveau token avec la variable en récursion jusqu'au dernier $
char	*ft_expand(shell_t *shell, char *token, int flag)
{
	char	*temp[4];

	temp[0] = ft_strchr(token, '$');
	temp[1] = ft_remove_char(ft_substr(token, 0, temp[0] - token), '\"');
	temp[2] = temp[0] + 1;
	while (++temp[0])
		if (!ft_isalnum(*temp[0]))
			break ;
	temp[2] = ft_substr(temp[2] , 0, temp[0] - temp[2] );
	temp[3] = ft_get_variable(shell, temp[2], 0);
	temp[3]  = ft_strjoin(temp[1], temp[3], 1);
	ft_free (temp[2]);
	temp[1] = ft_remove_char(ft_substr(temp[0], 0, ft_strlen(temp[0])), '\"');
	temp[0] = ft_strjoin(temp[3] , temp[1], 1);
	ft_free(temp[1]);
	if (flag == 1)
		ft_free (token);
	if (ft_strchr(temp[0], '$'))
		temp[0] = ft_expand(shell, temp[0], 1);
	return (temp[0]);
}

//on export une variable d'environement contenant le token etendu
char	*ft_expand_variable(shell_t *shell, char *token)
{
	char	*temps;
	char	*expand;

	if (token[0] == '$' && ft_strchr(&token[1], '$') == NULL)
		token = ft_get_variable(shell, &token[1], 0);
	else
	{
		if (token[0] == '\"')
			token = ft_expand(shell, token + 1, 0);
		else
			token = ft_expand(shell, token, 0);
		expand = ft_strjoin(&shell->expand[0], "-expand=", 0);
		temps = ft_strjoin(expand, token, 0);
		ft_free(token);
		ft_export(shell, temps, 0);
		ft_free(temps);
		expand[ft_strlen(expand) - 1] = '\0';
		token = ft_get_variable(shell, expand, 0);
		ft_free(expand);
		shell->expand[0] = shell->expand[0] + 1; 
	}
	return (token);
}

// on enleve les singles, doubles quotes et expand les variables
void	ft_clean_token(shell_t *shell, char **token)
{
	int t;

	t = 0;
	while (token[t])
	{
		if (token[t][0] == '\'' && token[t][ft_strlen(token[t]) - 1] == '\'')
			ft_remove_char(token[t], '\'');
		else if (token[t][0] == '\"' && token[t][ft_strlen(token[t]) - 1] == '\"')
		{
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(shell, token[t]);
			else
				ft_remove_char(token[t], '\"');
		}
		else
		{
			token[t] = ft_trim_token(token[t], ' ');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(shell, token[t]);
		}
		t++;
	}
}

// redirection can be call with < > or >>
void	ft_redirect(cmd_t *cmd, char *meta, int side, int flag)
{
	int i;
	int fd;

	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], meta, ft_strlen(meta)) == 0)
		{
			if (cmd->token[i][ft_strlen(meta)] == '\0')
			{
				fd = ft_open_fd(cmd->token[i + 1], flag);
				dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 2;
				else
					cmd->token[i] = NULL;
			}
			else
			{
				fd = ft_open_fd(&cmd->token[i][ft_strlen(meta)], flag);
				dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 1;
				else
					cmd->token[i] = NULL;
			}
		}
	}
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
		ft_free (test_path);
		test_path = NULL;
	}
	ft_free_array(fcnt_path);
	ft_free(program);
	return (test_path);
}

// trouve le chemin du programme
// si le chemin est trouvé on execute le programme
// sinon on affiche un message d'erreur et quitte le child
void	ft_execve(shell_t *shell, int nb)
{
	char	*cmd_path;
	
	cmd_path = ft_get_path(shell, nb);
	if (cmd_path != NULL) {
		execve(cmd_path, shell->cmd[nb].token, shell->env);
	}
	dprintf(2, "%s: command not found\n", shell->cmd[nb].token[0]);
	ft_free(cmd_path);
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
		ft_exit(shell, "Goodbye\n", 0);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(shell_t *shell, int nb)
{
	int	fd[2];
	
	if(pipe(fd) == -1)
		ft_exit(shell, "pipe error\n", 14);
	shell->pid[nb] = fork();
	if (shell->pid[nb] == 0)
	{
		if (nb < shell->nb_cmd - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_redirect(&shell->cmd[nb], ">>", 1, 6);
		ft_redirect(&shell->cmd[nb], ">", 1, 2);
		ft_redirect(&shell->cmd[nb], "<", 0, 1);
		ft_clean_token(shell, shell->cmd[nb].token);
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
		ft_exit(shell, "exit subshell", status);
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
	
	status = 0;
	ft_redirect(&shell->cmd[nb], ">>", 1, 6);
	ft_redirect(&shell->cmd[nb], ">", 1, 2);
	ft_redirect(&shell->cmd[nb], "<", 0, 1);
	ft_clean_token(shell, shell->cmd[nb].token);
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

//sur CTRL + C on print un retour a la ligne
//on se deplace sur une nouvelle ligne
//on efface la ligne
//on affiche le prompt
//on set le error status a 130
void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		error_status = 130;
	}
}

// on regarde si il y a un pipe au début ou fin du buffer
// si il y a 2 pipe collé on coupe le buffer
// si il y a seulement des espaces entre 2 pipes
int	ft_pipe_check(char *buf)
{
	char	*tmp;

	tmp = buf;
	if (buf[0] == '|' || buf[ft_strlen(buf) - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (*tmp)
	{
		if (*tmp == '|' && *(tmp + 1) == '|'){
			*tmp = '\0';
			return (0);
		}
		if (*tmp == '|' && ft_is_only(tmp + 1, ' ')){
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		tmp++;
	}
	return (0);
}

// on avance dans le buffer jusqu'a trouver un quote
// on regarde avec strchr si il y a une autre quote identique plus loin
// si non on retourne 1 et on affiche une erreur
// si oui on avance dans le buffer jusqu'a la quote identique et continue
int	ft_check_closed_quote(char *buf)
{
	char	*tmp;

	tmp = buf;
	while (*tmp){
		if (*tmp == '\'' || *tmp == '\"'){
			if (ft_strchr(tmp + 1, *tmp) == NULL){
				printf("Error Quote not closed\n");
				return (1);
			}
			else
				tmp = ft_strchr(tmp + 1, *tmp);
		}
		tmp++;
	}
	return (0);
}

// on skip les espaces et tabulations
// si le premier caractere set <$> et le suivant est <?>
// on imprime le status de la derniere commande
int	ft_status(shell_t *shell)
{
	int	i;

	i = 0;
	while (shell->buffer[i] && (shell->buffer[i] == ' '))
		i++;
	if (shell->buffer[i] == '$' && shell->buffer[i + 1] == '?'){
		printf("%d: command not found\n", error_status);
		error_status = 0;
		return (1);
	}
	return (0);
}

int ft_empty_token(char *buf)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buf);
	token = ft_strtok(tmp, '|');
	while(token)
	{
		if (ft_is_only(token, ' ')) {
			printf("parse error near `|'\n");
			ft_free(tmp);
			return (1);
		}
		i++;
		token = (ft_strtok(NULL, '|'));
	}
	ft_free(tmp);
	return (0);
}

// si la commande status est appelée
// si il y a des quotes non fermées
// si il y a des erreurs dans les pipes
int	ft_buffer_integrity(shell_t *shell)
{
	if (ft_status(shell))
		return (0);
	if (ft_check_closed_quote(shell->buffer))
		return (0);
	if 	(ft_pipe_check(shell->buffer))
		return (0);
	if (ft_empty_token(shell->buffer))
		return (0);
	return (1);
}

// créé le child pour créé le heredoc
void	ft_make_heredoc(shell_t *shell, char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		fd = ft_open_fd(heredoc, 2);
		if (fd == -1)
			ft_exit(shell, "Error: heredoc file not found", 1);
		while (1)
		{
			write(1, "<heredoc> ", 10);
			str = ft_get_next_line(0);
			if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
				&& str[ft_strlen(limiter) + 1] == '\0')
				break ;
			ft_putstr_fd(str, fd);
			free(str);
		}
		free(str);
		close(fd);
		ft_exit(shell, NULL, 3);
	}
	waitpid(pid, NULL, 0);
	printf("heredoc done\n");
}

// ajoute le heredoc dans l'environnement
char	*ft_expand_heredoc(shell_t *shell, char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", shell->heredoc, 0);
	expand = ft_strjoin(expand, "=", 1);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(shell, temps, 0);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	temps = ft_get_variable(shell, expand, 0);
	free(expand);
	shell->heredoc[0] = shell->heredoc[0] + 1;
	return (temps);
}

// cherche les heredoc et rem
void	ft_parse_heredoc(shell_t *shell, char **token)
{
	int i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			if (token[i][2] == '\0')
			{
				str = ft_expand_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(shell, token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str + 1;
			}
			else
			{
				str = ft_expand_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(shell, &token[i][2], str);
				token[i] = str;
			}
		}
	}
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
		shell->cmd[c].token = ft_calloc(sizeof(char *), count + 1);
		if (!shell->cmd[c].token)
			ft_exit(shell, "Error: malloc failed\n", 15);
		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		shell->cmd[c].save = shell->cmd[c].token;
		ft_print_table(shell);
		//ft_parse_heredoc(shell, shell->cmd[c].token);
		//ft_print_table(shell);
	}
}

// on check si le buffer est valide
// on compte le nombre de commandes et calloc le tableau de cmd
// on split le buffer en petit buffer pour chaque commande
int 	ft_parse(shell_t *shell)
{
	int i;

	i = 0;
	if (ft_buffer_integrity(shell) == 0)
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(shell_t), shell->nb_cmd);
	shell->pid = ft_calloc(sizeof(pid_t), shell->nb_cmd);
	if (shell->pid == NULL || shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15);
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
			if (ft_parse(shell))
				ft_execute_cmd(shell, 0);
			ft_clear_command(shell);
		}
		shell->buffer = ft_free(shell->buffer);
		shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
	return (0);
}

// Set le error status a 0
// calloc de la structure principal
// copie de la variable environ dans la structure
shell_t	*ft_init_minishell(char **env)
{
	shell_t *shell;

	error_status = 0;
	shell = ft_calloc(1, sizeof(shell_t));
	if (!shell)
		ft_exit(shell, "Error: malloc failed\n", 15);
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL){
		ft_exit(shell, "Error: malloc failed\n", 15);
	}
	return (shell);
}

// minishell
void	ft_minishell(char **env)
{
	shell_t *shell;

	shell = ft_init_minishell(env);
	signal(SIGINT, ft_signal);
	ft_getprompt(shell);
	ft_exit(shell, "Goodbye\n", 0);
}

// Main function
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	ft_minishell(env);
	return (0);
}
