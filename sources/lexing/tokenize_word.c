#include "lexing.h"

#include <stdio.h>

void	tokenize_word(t_input *input, size_t *i, char *line)
{
	char	*raw_content;
	size_t	j;

	j = *i;
	while (line[*i] && !is_whitespace(line[*i]) && !is_operator(line[*i]))
	{
		(*i)++;
		if (line[*i - 1] == '$' && is_quote(line[*i]))
			return;
	}
	raw_content = ft_strndup(&line[j], *i - j);
	printf("raw_content => %s\n",raw_content);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, ARG, raw_content);
	input->token_qty++;
}
