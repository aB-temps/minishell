#ifndef TOKEN_FOMATTING_H
# define TOKEN_FOMATTING_H

# include "parsing.h"

void	format_input(t_input *input);
void	format_command(t_input *input, t_token *array, ssize_t *i);
void	format_redir(t_input *input, ssize_t *i);
void	format_env_var(t_input *input, ssize_t *i);

#endif