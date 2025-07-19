#ifndef TOKEN_FOMATTING_H
# define TOKEN_FOMATTING_H

# include "parsing.h"

void	format_tokens(t_input *input);
void	format_command(t_input *input, t_token *array, ssize_t *i);
void	format_redir(t_input *input, ssize_t *i);
void	format_env_var(t_input *input, t_token *array, ssize_t *i);
size_t	countocc(char *s, char *to_find);
char	*str_replace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);
char	*get_env_var(char *var_name, t_input *input);
char	*substitute_env_var(char *s, t_input *input);

#endif