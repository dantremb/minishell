/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:17:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/11/22 19:58:35 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*read_fd(int fd, char *box);
char	*trim_ret(char *box);
char	*trim_box_free(char *box);

char	*ft_get_next_line(int fd)
{
	static char		*box;
	char			*ret;

	if (fd < 0)
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
	char	tmp[101];
	int		len;

	len = 1;
	while (ft_strchr(box, '\n') == NULL && len != 0)
	{
		len = read(fd, tmp, 100);
		if (len < 0)
			return (NULL);
		tmp[len] = '\0';
		box = ft_strjoin(box, tmp, 1);
	}
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
		free(box);
	else
	{
		tmp = ft_substr(box, ft_strchr(box, '\n') - box + 1,
				ft_strlen(ft_strchr(box, '\n') + 1));
		free (box);
		return (tmp);
	}
	return (NULL);
}
