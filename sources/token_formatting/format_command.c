#include "token_formatting.h"

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	char **temp;
	ssize_t j;
	ssize_t k;

	j = *i;
	k = *i + 1;
	while (j + 1 < input->token_qty && (array[j + 1].type == ARG || array[j
			+ 1].type == S_QUOTES || array[j + 1].type == D_QUOTES))
		j++;
	array[*i].type = COMMAND;
	array[*i].formatted_content = ft_strdup(array[*i].raw_content);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	while (k <= j)
	{
		array[*i].formatted_content = str_free_to_join(array[*i].formatted_content,
				" ");
		if (!array[*i].formatted_content)
			exit_minishell(input, EXIT_FAILURE);
		array[*i].formatted_content = str_free_to_join(array[*i].formatted_content,
				array[k].raw_content);
		if (!array[*i].formatted_content)
			exit_minishell(input, EXIT_FAILURE);
		k++;
	}
	temp = ft_split(array[*i].formatted_content, ' ');
	if (!temp)
		exit_minishell(input, EXIT_FAILURE);
	free(array[*i].formatted_content);
	array[*i].formatted_content = temp;
	*i = j + 1;
}