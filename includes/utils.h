#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>

char	**ft_tabdup(char **tab);
size_t	ft_tablen(char **tab);
size_t	countocc(char *s, char *to_find);
char	*str_replace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);
char	*str_chardel(char *s, char *c);
void	clear_env_list(void *var);

#endif