/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:28 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:48 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une chaine de caractère que l'on doit imprimer dans un fichier   */
/* on utilise donc la fonction Write avec le fichier en premier argument. la  */
/* chaine de caractère en deuxieme argument et finalement la longueur de la   */
/* chaine de caractère pour avoir le nombre de caractère a imprimer			  */

#include "../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
