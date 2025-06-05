#ifndef PARSING_H
# define PARSING_H

# include "input.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>

void	get_input(char **env);
bool	line_is_valid(char *line);
bool	is_whitespace(char c);
bool	is_operator(char c);
bool	is_valid_arg_char(char c);
t_input	*parse_input(char *line);
void	tokenize_input(t_input *input, char *line);
void	format_input(t_input *input);

#endif