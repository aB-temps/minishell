#ifndef UTILS_H
# define UTILS_H

# include "input.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

char	**ft_tabdup(char **tab);
size_t	ft_tablen(char **tab);
size_t	countocc(char *s, char *to_find);
char	*str_replace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);
char	*str_chardel(char *s, char *c);
char	*extract_var_key(char *s);
size_t	exp_var_strlen(char *s, t_vector *v_var_array);
void	clear_env_list_elem(void *var);
char	*gen_random_num_sequence(size_t len);
void	clear_hd_filename_elem(t_input *input, const char *temp_dir,
			char *fileid, char *full_path);
void	clear_var_vector(t_vector *v_var_array);
t_list	*lstgetprev(t_list *lst, t_list *elem);

#endif