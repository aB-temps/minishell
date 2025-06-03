#include "debug.h"
#include "parsing.h"

void	format_input(t_input *input)
{
	t_token	*array;
	char	**temp;
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;

	i = 0;
	j = 0;
	k = 0;
	array = (t_token *)input->v_tokens->array;
	temp = (void *)0;
	while (i < input->token_qty)
	{
		if (array[i].type >= REDIR_IN && array[i].type <= APPEND)
		{
			if (i + 1 < input->token_qty && array[i + 1].type == ARG)
			{
				array[i].formatted_content = ft_strdup(array[i
						+ 1].raw_content);
				if (!array[i].formatted_content)
					exit_minishell(input, EXIT_FAILURE);
				i++;
			}
			i++;
		}
		else if (array[i].type == ARG)
		{
			j = i;
			while (j + 1 < input->token_qty && array[j + 1].type == ARG)
				j++;
			array[i].type = COMMAND;
			array[i].formatted_content = ft_strdup(array[i].raw_content);
			if (!array[i].formatted_content)
				exit_minishell(input, EXIT_FAILURE);
			k = i + 1;
			while (k <= j)
			{
				array[i].formatted_content = str_free_to_join(array[i].formatted_content,
						" ");
				if (!array[i].formatted_content)
					exit_minishell(input, EXIT_FAILURE);
				array[i].formatted_content = str_free_to_join(array[i].formatted_content,
						array[k].raw_content);
				if (!array[i].formatted_content)
					exit_minishell(input, EXIT_FAILURE);
				k++;
			}
			temp = ft_split(array[i].formatted_content, ' ');
			if (!temp)
				exit_minishell(input, EXIT_FAILURE);
			free(array[i].formatted_content);
			array[i].formatted_content = temp;
			i = j + 1;
		}
		else
			i++;
	}
}
