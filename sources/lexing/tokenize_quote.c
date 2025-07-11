#include "lexing.h"

void	quoted_arg_len(char quote, size_t *i, char *line)
{
	size_t	count;

	count = 0;
	while (line[++(*i)])
	{
		if (line[*i] == quote)
		{
			count++;
			while (line[*i] && (count < 2 || (!is_whitespace(line[*i]) && !is_operator(line[*i]))))
			{
				count += (line[*i] == quote);
				(*i)++;
			}
			break ;
		}
	}
}

void	*tokenize_quote(t_input *input, size_t *i, char *line)
{
	ssize_t	j;
	int		token_type;
	char	*content;

	j = *i;
	while(!is_quote(line[*i]))
		(*i)++;
	if (line[*i] == '\'')
	{
		quoted_arg_len('\'', i, line);
		token_type = S_QUOTES;
	}
	else
	{
		token_type = D_QUOTES;
		quoted_arg_len('\"', i, line);
	}
	content = ft_strndup(&line[j], (*i) - j);
	if (!content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, content);
	input->token_qty++;
	return (input);
}
