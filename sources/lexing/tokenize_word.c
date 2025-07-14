#include "lexing.h"
#include <stdio.h>

void	tokenize_word(t_input *input, size_t *i, char *line)
{
	char	*raw_content;
	size_t	j;
	bool	to_link;

	j = *i;
	to_link = false;
	while (line[*i] && !is_whitespace(line[*i]) && !is_operator(line[*i])
		&& !is_quote(line[*i]))
		(*i)++;
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	if (is_quote(line[*i]) && !is_quote(line[*i + 1]))
		to_link = true;
	create_token(input, ARG, raw_content, to_link);
	input->token_qty++;
}
