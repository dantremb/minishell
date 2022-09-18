/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:17:47 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/18 02:11:48 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern t_data data;

void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
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

void	ft_env(int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (data.env[++i])
			printf("%s\n", data.env[i]);
	}
	else
	{
		while (data.env[++i])
		{
			if (data.env[i][0] != '<' && data.env[i][1] != '-' && ft_strchr(data.env[i], '='))
				printf("%s\n", data.env[i]);
		}
	}
}

void	ft_unset(char *buffer)
{
	int	i;

	i = -1;
	while (data.env[++i])
	{
		if (ft_strncmp(data.env[i], buffer, ft_strlen(buffer)) == 0
			&& data.env[i][ft_strlen(buffer)] == '=')
		{
			free(data.env[i]);
			while (data.env[i + 1])
			{
				data.env[i] = data.env[i + 1];
				i++;
			}
			data.env[i] = NULL;
		}
	}
}

void	ft_export(char *arg)
{
	char	**temp;
	char	*duplicate;
	int		i;

	if (ft_strchr(arg, '='))
	{
		duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		if (ft_get_variable(duplicate))
			ft_unset(duplicate);
		free (duplicate);
	}
	temp = ft_calloc(sizeof(char *), ft_array_size(data.env) + 2);
	if (temp == NULL)
		ft_exit("Malloc Error\n", 3);
	i = -1;
	while (data.env[++i])
		temp[i] = data.env[i];
	temp[i] = ft_strdup(arg);
	free(data.env);
	data.env = temp;
	if (arg == NULL)
		ft_env(0);
}

void	ft_cd(char *buffer)
{
	char	*temp[2];
	
	if (chdir(buffer) == 0)
	{
		ft_unset("OLDPWD");
		temp[0] = ft_get_variable("PWD");
		temp[1] = ft_strjoin("OLDPWD=", temp[0], 0);
		ft_export(temp[1]);
		free(temp[1]);
		ft_unset("PWD");
		temp[0] = getcwd(NULL, 0);
		temp[1] = ft_strjoin("PWD=", temp[0], 0);
		ft_export(temp[1]);
		free(temp[0]);
		free(temp[1]);
	}
	else
		printf("cd: %s: No such file or directory\n", buffer);
}
