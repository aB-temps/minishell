#include "token_formatting.h"

void	replace_env_var(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if ((array[i].type == D_QUOTES && array[i].raw_content[0] == '$')
			|| array[i].type == ENV_VAR)
			format_env_var(input, &i);
		else
			i++;
	}
}

void	format_input(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	i = 0;
	array = (t_token *)input->v_tokens->array;
	replace_env_var(input);
	while (i < input->token_qty)
	{
		if (array[i].type >= REDIR_IN && array[i].type <= APPEND)
			format_redir(input, &i);
		else if (array[i].type == ARG || array[i].type == ENV_VAR)
			format_command(input, array, &i);
		else
			i++;
	}
}
