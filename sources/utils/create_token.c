#include "parsing.h"

void	create_token(t_input *input, int type, char *raw_content)
{
	t_token	temp_token;

	init_token(&temp_token);
	temp_token.type = type;
	if (type == ARG)
		temp_token.raw_content = raw_content;
	else
	{
		temp_token.raw_content = ft_strdup(raw_content);
		if (!temp_token.raw_content)
			exit_minishell(input, EXIT_FAILURE);
	}
	if (!add_element(input->v_tokens, &temp_token))
	{
		if (type == ARG && raw_content)
			free(raw_content);
		exit_minishell(input, EXIT_FAILURE);
	}
}
