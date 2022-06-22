/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:54 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une chaine de caractere et un caractere de separation a utiliser */
/* pour séparer la premiere en plusieur "src" On dois faire un un premier     */
/* tableau de pointer vers chaque mots que nous allons extraire. J'ai fait une*/
/* petite fonction qui va compter le nombre de mot en avancant tant que nous  */
/* somme sur "sep", ajouter 1 mots si ce n'est plus "sep", aller jusqu'au     */
/* prochaine "sep" puis revenir au debut de la boucle. Losrque j'ai mon nombre*/
/* de mot je peut allouer mon premier tableau qui sera de la grandeur de la   */
/* grandeur d'un (char pointer) multiplier par le nombre de mot + 1 pour le   */
/* dernier '\0' Ensuite j'avance directement le pointer de "src" pour avancer */
/* dans la memoire de celui si. Quand je suis sur une case qui n'est pas "sep"*/
/* je cherche si il y a "sep" plus loin. Si il trouve "sep" j'appel a nouveau */
/* la fonction pour aller chercher le prochain "sep" en utilisant son retour  */
/* pour connaitre le nombre de caractère entre ma position actuel et le "sep" */
/* Je peut ensuite utiliser ft_substr pour créer une nouvelle chaine avec le  */
/* mot trouvé et le placer directement dans la case du tableau de pointer. Je */
/* replace mon pointer source après le mots trouvé et continue de chercher le */
/* prochain mot sauf si il n'y a pas de mot on fait que calculer la longueur  */
/* restante et faire ft_substr une derniere fois. On retour notre tableau de  */
/* pointer et aucune variable temporaire a besoin d'être free				  */

#include "../includes/libft.h"

static int	ft_count_word(char const *src, char sep)
{
	int		words;

	words = 0;
	while (*src)
	{
		while (*src == sep)
			src++;
		if (*src != sep && *src)
			words++;
		while (*src != sep && *src)
			src++;
	}
	return (words);
}

char	**ft_split(char const *src, char sep)
{
	char	**tab;
	int		words;
	int		i;
	int		len;

	words = ft_count_word(src, sep);
	tab = ft_calloc(sizeof(char *), (words + 1));
	i = -1;
	if (!tab)
		return (NULL);
	while (++i < words)
	{
		while (*src && *src == sep)
			src++;
		if (ft_strchr(src, sep))
			len = ft_strchr(src, sep) - src;
		else
			len = ft_strlen(src);
		tab[i] = ft_substr(src, 0, len);
		if (!tab[i])
			return (0);
		src += len;
	}
	return (tab);
}
