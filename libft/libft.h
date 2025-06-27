/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:50:13 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:50:25 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_typed_ptr
{
	int		type;
	void	**ptr_storage;
	void	*ptr_malloc;
}	t_typed_ptr;


int		ft_printf(const char *format, ...);
int		ft_eprintf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vdprintf(int fd, const char *format, va_list args);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

char	*get_next_line(int fd);
char	*join_list_to_str(t_str_list *start);

void	ft_cancel_newline_at_end(char *line);
char	*ft_remove_last_backslash(char *line);
int		ft_isspace(char c);
int		ft_isblank(char c);
int		ft_is_int_str(char *s);
int		ft_is_hex_str(char *s);
long	ft_atol(const char *nptr);
long	ft_htol(const char *nptr);

char	*ft_ptr_substr(const char *start, const char *end);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strip(const char *str);
int		ft_str_only_spaces(const char *test);
char	*ft_remove_quotes(char *start);
char	*ft_remove_all_outer_brackets(char *str);

void	ft_manage_quotes(char *str, int *quotes);
void	ft_manage_brackets(char *str, int quotes, int *brackets);
// char	*ft_strstr_outside(char *str, char *needle, int ignore_brackets);
// char	*ft_strstrs_outside(char *str, char *needles[], int ignore_brackets);
// char	*ft_strstrs_outside_rev(char *str, char *needles[], 
//			int ignore_brackets);
// char	*ft_strstr_outside_rev(char *str, char *needle, int ignore_brackets);
char	*ft_strend(char *str);
int		ft_check_quotes(char *str);

void	*set(void *vtarget, void *void_new);

int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isalnum(char c);
int		ft_isascii(int c);
int		ft_isprint(char c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_stpcpy(char *dst, const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
void	*ft_realloc(void *ptr, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	**ft_split(char const *s, char c);
size_t	ft_count_splits(char **split);
void	*ft_free_splits(void *vtable);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **begin_list, t_list *new);
int		ft_lstsize(t_list *begin_list);
t_list	*ft_lstprevious_last(t_list *somewhere);
t_list	*ft_lstlast(t_list *begin_list);
void	ft_lstadd_back(t_list **begin_list, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *begin_list, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstremove(t_list *to_remove, t_list **list, \
			void (*del)(void*));
t_list	*ft_lstelem_copy(t_list *src, \
			void * (*copy)(void *));
t_list	*ft_lstsub(t_list *left, t_list *right, \
		void * (*copy)(void *), void (*del)(void *));
t_list	*ft_lstfind(t_list *start, void *needle, \
			int (comp)(void *, void *));
t_list	*ft_lstfinds(t_list *start, void *needles[], \
			int (comp)(void *, void *));

#endif