/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:17:47 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/26 14:03:08 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
