#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>

char	**ft_tabdup(char **tab);
size_t	ft_tablen(char **tab);
size_t	count_occurence(char *s, char *to_find);
char	*str_replace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);

#endif