#include "token_formatting.h"

ssize_t	count_args(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	j;

	j = *i;
	while (j + 1 <= input->token_qty && !(array[j + 1].type >= PIPE && array[j
			+ 1].type <= APPEND))
		j++;
	return (j - *i + 1);
}

char	**join_args(t_input *input, t_token *array, ssize_t *i, size_t arg_qty)
{
	char	*joined_args;
	size_t	j;

	j = 1;
	joined_args = ft_strdup(array[*i].raw_content);
	if (!joined_args)
		exit_minishell(input, EXIT_FAILURE);
	while (j < arg_qty - 1)
	{
		joined_args = str_free_to_join(joined_args, " ");
		if (!joined_args)
			exit_minishell(input, EXIT_FAILURE);
		if (array[*i + j].type == ENV_VAR)
			joined_args = str_free_to_join(joined_args, array[*i
					+ j].formatted_content);
		else
			joined_args = str_free_to_join(joined_args, array[*i
					+ j].raw_content);
		if (!joined_args)
			exit_minishell(input, EXIT_FAILURE);
		j++;
	}
	return (ft_split(joined_args, ' '));
}

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	args;

	args = count_args(input, array, i);
	array[*i].type = COMMAND;
	array[*i].formatted_content = join_args(input, array, i, args);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	(*i) += args;
}
