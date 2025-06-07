#include "lexing.h"

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (is_redir_or_pipe(line[*i]))
		tokenize_redir(input, i, line, line_len);
	else if (is_var(line[*i]))
	{
		if (is_in_string(line, '='))
			tokenize_arg(input, i, ASSIGN, line);
		else
			tokenize_arg(input, i, ENV_VAR, line);
	}
}