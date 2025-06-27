#include "exec.h"
#include <stdio.h>

static int	execute_child(t_exec *exec, t_fd *fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(exec->cmd_path);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		prepare_pipe(exec, fd, i);
		execve(exec->cmd_path, exec->args, exec->env);
		perror("execve");
		exit(126);
	}
	free(exec->cmd_path);
	return (pid);
}

static int	handle_command_not_found(char **args, char *cmd_path)
{
	if (!cmd_path)
	{
		ft_putstr_fd("command not found : ", 2);
		ft_putendl_fd(*args, 2);
		return (-1);
	}
	return (0);
}

int	execute_command(t_token *current_token, t_exec *exec, t_fd *fd, int i)
{

	int		pid;

	exec->args = (char **)(current_token->formatted_content);
	exec->cmd_path = find_full_command_path(exec->args[0], exec->env);
	if (handle_command_not_found(exec->args, exec->cmd_path) == -1)
		return (-1);
	pid = execute_child(exec, fd, i);
	return (pid);
}
