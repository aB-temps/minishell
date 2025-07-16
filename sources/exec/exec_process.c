#include "exec.h"
#include "input.h"
#include <stdio.h>

int	free_child(t_exec *exec, t_input *input)
{
	free(exec->cmd_path);
	clear_vector(&input->v_tokens);
	free(input);
	free(exec->pid_child);
	return (127);
}

static int	execute_child(t_exec *exec, t_fd *fd, int i, t_input *input)
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
		if (!exec->cmd_path)
			exit(free_child(exec, input));
		execve(exec->cmd_path, exec->args, input->env->array);
		perror("execve");
		exit(126);
	}
	free(exec->cmd_path);
	return (pid);
}

int	execute_command(t_token *current_token, t_exec *exec, t_fd *fd, int i,
		t_input *input)
{
	int	pid;

	pid = 0;
	exec->args = (char **)(current_token->formatted_content);
	exec->cmd_path = find_full_command_path(exec->args[0], input->env->array);
	pid = execute_child(exec, fd, i, input);
	return (pid);
}
