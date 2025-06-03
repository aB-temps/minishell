#include "exec.h"
#include <errno.h>

t_token	*get_token_at_index(t_vector *vec, size_t index)
{
	if (!vec || !vec->array || index >= vec->nb_elements)
		return (NULL);
	return ((t_token *)((char *)vec->array + (index * vec->datatype_size)));
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	cleanup_command_resources(char **args, char *cmd_path)
{
	if (args)
		free(args);
	if (cmd_path)
		free(cmd_path);
}

static void	execute_all_commands(t_input *input, char **env)
{
	int	*pids;
	int	cmd_count;

	cmd_count = count_commands(input);
	if (cmd_count == 0)
		return ;
	pids = ft_calloc(cmd_count, sizeof(int));
	if (!pids)
		return ;
	launch_all_commands(input, env, pids);
	wait_for_processes(pids, cmd_count);
	free(pids);
	// printf("All cmd executed\n\n"); //debug
}

void	exec_cmd(t_input *input, char **env)
{
	// debug_print_all_tokens(input, env);
	execute_all_commands(input, env);
}
