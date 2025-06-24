#include "debug.h"
#include "exec.h"
#include <errno.h>

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

static int	execute_all_commands(t_input *input, char **env)
{
	int	*pids;
	int	cmd_count;

	// cmd_count = input->token_qty;
	cmd_count = count_cmd(input);
	pids = ft_calloc(cmd_count, sizeof(int));
	if (!pids)
		return (1);
	debug_print_all_arrays(input, pids, input->token_qty); //debug
	launch_all_commands(input, env, pids);
	wait_for_processes(pids, cmd_count);
	free(pids);
	// printf("All cmd executed\n\n"); //debug
	return (0);
}

int	exec_cmd(t_input *input, char **env)
{
	if (execute_all_commands(input, env) == 1)
		return (1);
	return (0);
}
