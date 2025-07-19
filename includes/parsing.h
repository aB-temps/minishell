#ifndef PARSING_H
# define PARSING_H

# include "lexing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

void	get_input(char **env);
void	*parse_input(t_input *input);
void	format_input(t_input *input);
void	handle_heredoc(t_input *input);

#endif