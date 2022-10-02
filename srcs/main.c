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
	if (ft_check_closed_quote(shell->buffer) == 0 || ft_status(shell))
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
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
				//ft_execute_cmd(shell, 0);
				ft_free(shell, 4);
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
