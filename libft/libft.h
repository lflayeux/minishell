/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:28:20 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/07 00:12:35 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//LIBFT

void	*ft_memcpy(void *dest, const void *src, size_t n);

int		ft_atoi(const char *str);

void	ft_bzero(void *s, size_t n);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memset(void *s, int c, size_t n);

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *str, int c);

char	*ft_strdup(const char *s);

char	*ft_strjoin(char const *s1, char const *s2);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

size_t	ft_strlcat(char *dst, const char *src, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t len);

size_t	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char*big, const char *little, size_t len);

char	*ft_strrchr(const char *str, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

void	*ft_calloc(size_t nb, size_t size);

int		ft_strcmp(const char *s1, const char *s2);

void	ft_free_tab(void **tab);

int		ft_intlen(int nb);

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_realloc(char *full_buf, char *buf);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
int		ft_strchr_split(char *str, char c);
char	*ft_read(char *full_buf, int fd);
char	*ft_line(char *full_buf);
char	*ft_stay(char *full_buf);
char	*get_next_line(int fd);
void	*ft_calloc_gnl(size_t nb, size_t size);

// FT_PRINTF

int		ft_putnbrhexa(unsigned long int nb);
int		ft_putnbrhexa_up(unsigned long int nb);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putnbr(long int nb);
int		ft_printf(const char *format, ...);

#endif
