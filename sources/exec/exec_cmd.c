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

static int	execute_all_commands(t_input *input, t_exec *exec)
{

	exec->cmd_count = count_cmd(input);
	exec->pid_children = ft_calloc(exec->cmd_count, sizeof(pid_t));
	if (!exec->pid_children)
		return (1);
	//debug_print_all_arrays(input, exec->pid_children, input->token_qty); //debug
	launch_all_commands(input, exec);
	wait_for_processes(exec->pid_children, exec->cmd_count);
	free(exec->pid_children);
	return (0);
}

int	exec_cmd(t_input *input, char **env)
{
	t_exec exec;

	exec.env = env;
	exec.infile = NULL;
	exec.outfile = NULL;
	exec.cmd_path = NULL;
	exec.args = NULL;
	if (execute_all_commands(input, &exec) == 1)
		return (1);
	return (0);
}
