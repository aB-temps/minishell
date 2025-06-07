#include "lexing.h"

void	tokenize_arg(t_input *input, size_t *i, int token_type, char *line)
{
	char	*raw_content;
	size_t	j;

	j = *i;
	while (line[*i] && is_valid_arg_char(line[*i]))
		(*i)++;
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, raw_content);
	input->token_qty++;
}