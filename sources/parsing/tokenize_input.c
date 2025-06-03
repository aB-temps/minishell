#include "parsing.h"

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	t_token	token;

	init_token(&token);
	if (line[*i] == '|')
		create_token(input, &token, PIPE, "|");
	else if (line[*i] == '>')
	{
		if (*i < line_len - 1 && line[*i + 1] == '>')
		{
			create_token(input, &token, APPEND, ">>");
			(*i)++;
		}
		else
			create_token(input, &token, REDIR_OUT, ">");
	}
	else if (line[*i] == '<')
		create_token(input, &token, REDIR_IN, "<");
	input->token_qty++;
}

void	tokenize_input(t_input *input, char *line)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (is_operator(line[i]))
			tokenize_operator(input, &i, line, line_len);
		/* if (is_quote(line[i]))
			i += tokenize_quote(input, i, line, line_len);
		// comment je vais faire ca zebi faudra prendre les strings nik zebi */
		i++;
	}
	print_input(input);
}
