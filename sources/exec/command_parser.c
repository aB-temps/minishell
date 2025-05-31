#include "exec.h"

char	**build_args_array(t_input *input, int start_idx, int end_idx)
{
	char	**args;
	t_token	*token;
	int		i;
	int		j;

	i = start_idx;
	args = ft_calloc((end_idx - start_idx + 1), sizeof(char *));
	if (!args)
		return (NULL);
	j = 0;
	while (i < end_idx)
	{
		token = get_token_at_index(input->v_tokens, i);
		if (!token)
		{
			i++;
			continue ;
		}
		if (token->type == COMMAND || token->type == ARG)
			args[j++] = token->raw_content;
		i++;
	}
	args[j] = NULL;
	return (args);
}

ssize_t	find_next_command(t_input *input, ssize_t start)
{
	ssize_t	i;
	t_token	*token;

	i = start;
	while (i < input->token_qty)
	{
		token = get_token_at_index(input->v_tokens, i);
		if (token && token->type == COMMAND)
			return (i);
		i++;
	}
	return (-1);
}

ssize_t	find_command_end(t_input *input, ssize_t start)
{
	ssize_t	i;
	t_token	*token;

	i = start;
	while (i < input->token_qty)
	{
		token = get_token_at_index(input->v_tokens, i);
		if (token && token->type == PIPE)
			return (i);
		i++;
	}
	return (input->token_qty);
}

int	count_commands(t_input *input)
{
	ssize_t	cmd_start;
	ssize_t	cmd_end;
	int		cmd_count;

	cmd_count = 0;
	cmd_start = find_next_command(input, 0);
	while (cmd_start != -1)
	{
		cmd_count++;
		cmd_end = find_command_end(input, cmd_start);
		cmd_start = find_next_command(input, cmd_end + 1);
	}
	return (cmd_count);
}
