#include "exec.h"

// static int	has_pipes(t_input *input)
// {
// 	int		i;
// 	t_token	*tokens_array;

// 	i = 0;
// 	tokens_array = (t_token *)input->v_tokens->array;
// 	while (i < input->token_qty)
// 	{
// 		if (tokens_array[i].type == PIPE)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	prepare_pipe(t_exec *exec, t_fd *fd, int i)
{
	if (i == 0)
		first_cmd(fd, exec->infile);
	else if (i == exec->cmd_count - 1)
		last_cmd(fd, exec->outfile);
	else
		middle_cmd(fd);
}

int	launch_all_commands(t_input *input, t_exec *exec)
{
	t_token	*current_token;
	t_token	*tokens_array;
	t_fd	fd;
	int		i;
	int		y;

	printf("%d\n", exec->cmd_count);
	y = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	init_fd(&fd);
	if (pipe(fd.fd1) == -1)
	{
		close_all(&fd);
		return (1);
	}
	while (i < count_cmd(input))
	{
		current_token = &tokens_array[y];
		if (current_token->type == COMMAND)
		{
			if (pipe(fd.fd2) == -1)
			{
				close_all(&fd);
				return (1);
			}
			dprintf(1, "test\n");
			exec->pid_children[y] = execute_command(current_token, exec, &fd,
					i);
		}
		else
			y++;
		i++;
	}
	// current_token = &tokens_array[i];
	// exec->pid_children[i] = execute_command(current_token, exec, &fd, i);
	return (0);
}

int	wait_for_processes(int *pids, int cmd_count)
{
	int	j;
	int	status;
	int	last_pid;
	int	wait_ret;

	last_pid = -1;
	j = 0;
	while (j < cmd_count)
	{
		if (pids[j] > 0)
		{
			wait_ret = waitpid(pids[j], &status, 0);
			if (wait_ret > 0)
			{
				if (WIFEXITED(status))
				{
					printf("Command %d (PID %d) exited with status %d\n", j,
						pids[j], WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					printf("Command %d was killed by signal %d\n", j,
						WTERMSIG(status));
				}
				else
				{
					printf("Command %d terminated abnormally\n", j);
				}
				last_pid = pids[j];
			}
			else
			{
				perror("waitpid failed");
			}
		}
		j++;
	}
	return (last_pid);
}
