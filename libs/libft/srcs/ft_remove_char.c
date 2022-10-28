/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:19:03 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 18:21:55 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_remove_char(char *token, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == sep)
		{
			j = i - 1;
			while (token[++j])
				token[j] = token[j + 1];
		}
		else
			i++;
	}
	return (token);
}
