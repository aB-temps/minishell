#ifndef PARSING_H
# define PARSING_H

# include "input.h"
# include "lexing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

void	get_input(char **env);
t_input	*parse_input(char *line, char *prompt);
void	format_input(t_input *input);

#endif