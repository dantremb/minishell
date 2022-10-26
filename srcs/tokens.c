/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:36:08 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/26 14:07:04 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int error_status;

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
