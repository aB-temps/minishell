#include "token_formatting.h"

ssize_t	count_args(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	j;

	j = *i;
	while (j + 1 <= input->token_qty && !(array[j + 1].type >= PIPE && array[j
			+ 1].type <= APPEND))
		j++;
	return (j - *i);
}

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	char	**temp;
	ssize_t	j;
	ssize_t	k;

	temp = (void *)0;
	k = 0;
	j = count_args(input, array, i);
	array[*i].formatted_content = ft_strdup(array[*i].raw_content);
	while (k < j)
	{
		if (array[*i + k].type == ENV_VAR)
			array[*i].formatted_content = str_free_to_join(array[*i
					+ k].formatted_content, " ");
		else
			array[*i].formatted_content = str_free_to_join(array[*i].formatted_content,
					array[*i + k].formatted_content);
		if (!array[*i].formatted_content)
			exit_minishell(input, EXIT_FAILURE);
		k++;
	}
	temp = ft_split(array[*i].formatted_content, ' ');
	if (!temp)
		exit_minishell(input, EXIT_FAILURE);
	free(array[*i].formatted_content);
	array[*i].formatted_content = temp;
	*i += k;
}
