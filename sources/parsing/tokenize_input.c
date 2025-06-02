#include "parsing.h"

int	tokenize_operator(t_input *input, size_t i, char *line, size_t line_len)
{
	t_token	token;
	size_t		j;

	j = 0;
	init_token(&token);
	if (line[i] == '|')
		token.type = PIPE;
	else if (line[i] == '>')
	{
		if (i < line_len - 1 && line[i + 1] == '>')
		{
			token.type = APPEND;
			j++;
		}
		else
			token.type = REDIR_OUT;
	}
	else if (line[i] == '<')
		token.type = REDIR_IN;
	if (!add_element(input->v_tokens, &token))
	{
		clear_vector(input->v_tokens);
		free(input);
		exit(EXIT_FAILURE);
	}
	input->token_qty++;
	return (j);
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
			i += tokenize_operator(input, i, line, line_len);
		/* if (is_quote(line[i]))
			i += tokenize_quote(input, i, line, line_len);
		// comment je vais faire ca zebi faudra prendre les strings nik zebi */
		i++;
	}
}
