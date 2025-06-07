#include "lexing.h"

void	tokenize_redir(t_input *input, size_t *i, char *line, size_t line_len)
{
	if (line[*i] == '|')
		create_token(input, PIPE, "|");
	else if (line[*i] == '>')
	{
		if (*i < line_len - 1 && line[*i + 1] == '>')
		{
			create_token(input, APPEND, ">>");
			(*i)++;
		}
		else
			create_token(input, REDIR_OUT, ">");
	}
	else if (line[*i] == '<')
		create_token(input, REDIR_IN, "<");
	(*i)++;
	input->token_qty++;
}