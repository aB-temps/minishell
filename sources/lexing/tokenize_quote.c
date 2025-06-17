#include "lexing.h"

void	slice_quotes(char quote, size_t *i, char *line)
{
	size_t	count;

	count = 0;
	while (line[++(*i)])
	{
		if (line[*i] == quote)
		{
			count++;
			while (count < 2 && line[*i] && !is_whitespace(line[*i]))
			{
				if (line[*i] == quote)
					count++;
				(*i)++;
			}
			break ;
		}
	}
}

void	*tokenize_quote(t_input *input, size_t *i, int token_type, char *line)
{
	ssize_t	j;
	char	*content;

	j = *i;
	if (line[*i] == '\'')
	{
		slice_quotes('\'', i, line);
		token_type = S_QUOTES;
	}
	else
	{
		token_type = D_QUOTES;
		slice_quotes('\"', i, line);
	}
	/* while (line[++(*i)])
	{
		if ((token_type == S_QUOTES && line[*i] == '\'')
				|| (token_type == D_QUOTES && line[*i] == '"'))
		{
			while (line[*i] && !is_whitespace(line[*i]))
				(*i)++;
			break ;
		}
	} */
	content = ft_strndup(&line[j], (*i) - j);
	if (!content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, content);
	input->token_qty++;
	return (input);
}
