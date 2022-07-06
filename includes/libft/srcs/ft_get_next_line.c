/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:17:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/07/05 11:41:52 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*read_fd(int fd, char *box);
char	*trim_ret(char *box);
char	*trim_box_free(char *box);
char	*ft_strjoin_and_free(char const *s1, char const *s2);

char	*ft_get_next_line(int fd)
{
	static char		*box;
	char			*ret;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	box = read_fd(fd, box);
	if (!box)
		return (NULL);
	ret = trim_ret(box);
	box = trim_box_free(box);
	return (ret);
}

char	*read_fd(int fd, char *box)
{
	char	*tmp;
	int		len;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	len = 1;
	while (ft_strchr(box, '\n') == NULL && len != 0)
	{
		len = read(fd, tmp, BUFFER_SIZE);
		if (len < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[len] = '\0';
		box = ft_strjoin_and_free(box, tmp);
	}
	free (tmp);
	return (box);
}

char	*trim_ret(char *box)
{
	char	*ret;

	if (!box[0])
		return (NULL);
	if (ft_strchr(box, '\n') == NULL)
		ret = ft_strdup(box);
	else
		ret = ft_substr(box, 0, ft_strchr(box, '\n') - box + 1);
	return (ret);
}

char	*trim_box_free(char *box)
{
	char	*tmp;

	if (ft_strchr(box, '\n') == NULL)
	{
		free(box);
		return (NULL);
	}
	else
	{
		tmp = ft_substr(box, ft_strchr(box, '\n') - box + 1,
				ft_strlen(ft_strchr(box, '\n') + 1));
		free (box);
		return (tmp);
	}
}

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	char	*tmp;
	int		is;
	int		id;

	is = 0;
	id = 0;
	if (!s1)
		s1 = ft_strdup("\0");
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tmp == NULL)
		return (NULL);
	while (s1[is] != '\0')
	{
		tmp[is] = s1[is];
		is++;
	}
	while (s2[id] != '\0')
	{
		tmp[is] = s2[id];
		is++;
		id++;
	}
	tmp[is] = '\0';
	free ((void *)s1);
	return (tmp);
}
