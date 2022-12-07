/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:12:22 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/07 11:10:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

void	ft_env(int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (g_env[++i])
			printf("[%d]%s\n", i, g_env[i]);
	}
	else
	{
		while (g_env[++i])
		{
			if (g_env[i][0] != '<' && g_env[i][1] != '-'
				&& ft_strchr(g_env[i], '='))
				printf("%s\n", g_env[i]);
		}
	}
}

void	ft_unset(char *buffer)
{
	int	i;

	i = -1;
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], buffer, ft_strlen(buffer)) == 0
			&& g_env[i][ft_strlen(buffer)] == '=')
		{
			ft_free(g_env[i]);
			while (g_env[i + 1])
			{
				g_env[i] = g_env[i + 1];
				i++;
			}
			g_env[i] = NULL;
		}
	}
}

void	ft_export(t_shell *shell, char *arg, int flag)
{
	char	*duplicate;

	if (arg && ft_isalpha(arg[0]) == 0 && flag == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->error = 1;
	}
	else
	{
		if (ft_strchr(arg, '='))
		{
			duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
			if (ft_get_variable(duplicate, 0))
				ft_unset(duplicate);
			ft_free (duplicate);
		}
		g_env = ft_remalloc(g_env, 1, 1);
		g_env[ft_array_size(g_env) - 1] = ft_strdup(arg);
	}
}

void	ft_cd(t_shell *shell, char *buffer)
{
	char	*temp[2];

	if (!buffer)
		buffer = ft_get_variable("HOME", 0);
	if (buffer && chdir(buffer) == 0)
	{
		ft_unset("OLDPWD");
		temp[0] = ft_get_variable("PWD", 0);
		temp[1] = ft_strjoin("OLDPWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		ft_free(temp[1]);
		ft_unset("PWD");
		temp[0] = getcwd(NULL, 0);
		temp[1] = ft_strjoin("PWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		ft_free(temp[0]);
		ft_free(temp[1]);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(buffer, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n", 2) == 0)
	{
		if (ft_is_only(&arg[1][1], 'n'))
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

