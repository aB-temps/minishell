#include "lexing.h"

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (is_redir_or_pipe(line[*i]))
		tokenize_redir(input, i, line, line_len);
	else if (is_var_or_assign(line[*i]))
		tokenize_arg(input, i, ENV_VAR, line);
}