#ifndef LEXING_H
# define LEXING_H

# include "checking.h"
# include "input.h"

void	*tokenize_input(t_input *input, char *line);
void	tokenize_word(t_input *input, size_t *i, char *line);
void	tokenize_operator(t_input *input, size_t *i, char *line,
			size_t line_len);
void	*tokenize_quote(t_input *input, size_t *i, char *line);
#endif