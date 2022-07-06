/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:40:58 by root              #+#    #+#             */
/*   Updated: 2022/06/30 14:17:40 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define DEC "0123456789"
# define HEXU "0123456789ABCDEF"
# define HEXL "0123456789abcdef"
# define BUFFER_SIZE 500

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void			ft_putchar(char str);
void			ft_putstr(char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int nbr, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_bzero(void *str, size_t len);
void			*ft_calloc(size_t nbr, size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *str, int nbr, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_striteri(char *src, void (*f)(unsigned int, char*));
int				ft_isdigit(int nbr);
int				ft_isalpha(int nbr);
int				ft_isascii(int nbr);
int				ft_isalnum(int nbr);
int				ft_isprint(int nbr);
int				ft_toupper(int nbr);
int				ft_tolower(int nbr);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t len);
long int		ft_atoli(const char *str);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strcat(char *dest, char *src);
char			*ft_itoa(int nbr);
char			*ft_strdup(const char *src);
char			*ft_strchr(const char *str, int nbr);
char			**ft_split(char const *src, char sep);
char			*ft_strrchr(const char *str, int nbr);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *src, unsigned int start, size_t len);
char			*ft_strnstr(const char *src, const char *find, size_t len);
char			*ft_strmapi(char const *src, char (*f)(unsigned int, char));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *));
char			*ft_get_next_line(int fd);
int				ft_printf(const char *str, ...);
void			ft_choose_arg(char str, va_list arg, int *p);
void			ft_put_str(const char *str, int *p);
void			ft_put_char(char src, int *p);
void			ft_put_nbr(int nbr, int *p);
void			ft_put_ptr(unsigned long int nbr, int *p);
void			ft_put_hex(unsigned long int nbr, unsigned int base,
					char *hex, int *p);
void			ft_free_array(char **array);
int				ft_split_size(char *src, char sep);

#endif
