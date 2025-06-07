#include "debug.h"
#include "parsing.h"

void	format_env_var(t_input *input, ssize_t *i)
{
	t_token	*array;
	char	*content;

	array = (t_token *)input->v_tokens->array;
	content = getenv(&array[*i].raw_content[1]);
	array[*i].type = ARG;
	array[*i].formatted_content = ft_strdup(content);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	(*i)++;
}

void	format_command(t_input *input, ssize_t *i)
{
	t_token	*array;
	char	**temp;
	ssize_t	j;
	ssize_t	k;

	array = (t_token *)input->v_tokens->array;
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

void	format_redir(t_input *input, ssize_t *i)
{
	t_token	*array;

	array = (t_token *)input->v_tokens->array;
	if (array[(*i)].type >= REDIR_IN && array[(*i)].type <= APPEND)
	{
		if ((*i) + 1 < input->token_qty && array[(*i) + 1].type == ARG)
		{
			array[(*i)].formatted_content = ft_strdup(array[(*i)
					+ 1].raw_content);
			if (!array[(*i)].formatted_content)
				exit_minishell(input, EXIT_FAILURE);
			(*i)++;
		}
		(*i)++;
	}
}

void	replace_env_var(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if ((array[i].type == D_QUOTES && array[i].raw_content[1] == '$')
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
		else if (array[i].type == ARG)
			format_command(input, &i);
		else
			i++;
	}
}
