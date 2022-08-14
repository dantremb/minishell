/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:40:45 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/14 11:45:00 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;
//path absolue
//export PATH=$PATH:/usr/local/bin

bool	ft_subpath(int i, int k)
{
	size_t	len;
	char	*save;

	len = ft_strlen(environ[i]);
	if (chdir("..") >= 0)
	{
		free(environ[k]);
		environ[k] = ft_strjoin("OLD", environ[i], 0);
		while (environ[i][len] != '/')
			len--;
		environ[i][len] = '\0';
		save = ft_strdup(environ[i]);
		free(environ[i]);
		environ[i] = ft_strdup(save);
		free(save);
		return (true);
	}
	return (false);
}

bool	change_dir(char *buffer, int i, int k)
{
	if (chdir(buffer) >= 0)
	{
		free(environ[k]);
		free(environ[i]);
		environ[k] = ft_strjoin("OLD", environ[i], 0);
		environ[i] = ft_strjoin(environ[i], ft_strjoin("/", buffer, 0), 1);
	}
	else
	{
		printf("Error, wrong directory\n");
		return (false);
	}
	return (true);
}

bool	ft_cd(char *buffer)
{
	bool	ret;
	int		i;
	int		k;

	ret = false;
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PWD=", 4))
		i++;
	k = 0;
	while (environ[k] && ft_strncmp(environ[k], "OLDPWD=", 7))
		k++;
	if (ft_strncmp(buffer, "..", 2) == 0)
		ret = ft_subpath(i, k);
	else
		ret = change_dir(buffer, i, k);
	return (ret);
}

