#ifndef LEXING_H
# define LEXING_H

# include "input.h"

void	*tokenize_input(t_input *input, char *line);
void	tokenize_arg(t_input *input, size_t *i, int token_type, char *line);
void	tokenize_operator(t_input *input, size_t *i, char *line,
			size_t line_len);
void	*tokenize_quote(t_input *input, size_t *i, int token_type, char *line);
void	tokenize_redir(t_input *input, size_t *i, char *line, size_t line_len);
#endif