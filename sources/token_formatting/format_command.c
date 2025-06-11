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

char	**args_to_array(t_input *input, t_token *array, ssize_t *i,
		size_t arg_qty)
{
	char	**args_array;
	size_t	j;
	size_t	k;

	j = 0;
	k = *i;
	args_array = malloc(sizeof(char *) * arg_qty + 1);
	if (!args_array)
		exit_minishell(input, EXIT_FAILURE);
	while (j < arg_qty - 1)
	{
		if (array[k].type == ENV_VAR)
			args_array[j] = ft_strdup(array[k].formatted_content);
		else
			args_array[j] = ft_strdup(array[k].raw_content);
		if (!args_array[j])
			exit_minishell(input, EXIT_FAILURE);
		j++;
		k++;
	}
	args_array[arg_qty - 1] = (void *)0;
	return (args_array);
}

void	format_command(t_input *input, t_token *array, ssize_t *i)
{
	ssize_t	arg_qty;

	arg_qty = count_args(input, array, i);
	array[*i].formatted_content = args_to_array(input, array, i, arg_qty);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = COMMAND;
	(*i) += arg_qty;
}
