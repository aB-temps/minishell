#include "lexing.h"

static void	tokenize_redir(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (line[*i] == '>')
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
	{
		if (*i < line_len - 1 && line[*i + 1] == '<')
		{
			create_token(input, HEREDOC, "<<");
			(*i)++;
		}
		else
			create_token(input, REDIR_IN, "<");
	}
	(*i)++;
	input->token_qty++;
}

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (line[*i] == '|')
	{
		create_token(input, PIPE, "|");
		(*i)++;
		input->token_qty++;
	}
	else
		tokenize_redir(input, i, line, line_len);
}
