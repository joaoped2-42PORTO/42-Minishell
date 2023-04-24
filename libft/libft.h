/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:30:20 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/07 15:37:31 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
void	*ft_memset(void *str, int c, size_t n);
char	*ft_strrchr(const char *str, int c);
void	ft_bzero(void *str, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_atoi(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_isalpha(int c);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_isdigit(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
int		ft_isascii(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
int		ft_isprint(int c);
size_t	ft_strlcat(char *dest, const char *src, size_t destlen);
int		ft_toupper(int c);
char	*ft_strchr(const char *str, int c);
int		ft_tolower(int c);
void	*ft_calloc(size_t n, size_t daty);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *str);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
