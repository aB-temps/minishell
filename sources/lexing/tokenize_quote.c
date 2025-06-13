#include "lexing.h"

void	*tokenize_quote(t_input *input, size_t *i, int token_type, char *line)
{
	ssize_t	j;
	char	*content;

	// j = *i + 1;
	j = *i;
	if (line[*i] == '\'')
		token_type = S_QUOTES;
	else
		token_type = D_QUOTES;
	while (line[++(*i)])
	{
		if ((token_type == S_QUOTES && line[*i] == '\'')
				|| (token_type == D_QUOTES && line[*i] == '"'))
		{
			if (!line[*i + 1] || is_whitespace(line[*i + 1]))
				break ;
		}
	}
	content = ft_strndup(&line[j], (*i)++ - j + 1);
	if (!content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, content);
	input->token_qty++;
	return (input);
}
