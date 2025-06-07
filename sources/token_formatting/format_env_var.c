#include "token_formatting.h"

void	format_env_var(t_input *input, ssize_t *i)
{
	t_token	*array;
	char	*content;

	array = (t_token *)input->v_tokens->array;
	array[*i].type = ARG;
	content = getenv(&array[*i].raw_content[1]);
	if (ft_strlen(content) == 0)
		array[*i].formatted_content = (void *)0;
	array[*i].formatted_content = ft_strdup(content);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	(*i)++;
}

