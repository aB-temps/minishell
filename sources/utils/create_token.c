#include "parsing.h"

void	create_token(t_input *input, t_token *temp_token, int type,
		char *raw_content)
{
	temp_token->type = type;
	temp_token->raw_content = malloc(sizeof(char) * ft_strlen(raw_content) + 1);
	if (!temp_token->raw_content)
	{
		clear_vector(input->v_tokens);
		free(input);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(temp_token->raw_content, raw_content, ft_strlen(raw_content)
		+ 1);
	if (!add_element(input->v_tokens, temp_token))
	{
		clear_vector(input->v_tokens);
		free(input);
		exit(EXIT_FAILURE);
	}
}
