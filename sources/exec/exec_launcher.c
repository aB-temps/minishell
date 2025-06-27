#include "exec.h"

int	launch_all_commands(t_input *input, t_exec *exec)
{
	t_token	*current_token;
	t_token	*tokens_array;
	t_fd	fd;
	int		i;
	int		y;

	y = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	init_fd(&fd);
	while (i < count_cmd(input))
	{
		current_token = &tokens_array[y];
		if (current_token->type == COMMAND)
		{
			if (i < exec->cmd_count - 1)
			{
				if (pipe(fd.fd2) == -1)
				{
					close_all(&fd);
					return (1);
				}
			}
			exec->pid_children[i] = execute_command(current_token, exec, &fd,
					i);
			close(fd.fd1[0]);
			if (i < exec->cmd_count - 1)
			{
				close(fd.fd2[1]);
				fd.fd1[0] = fd.fd2[0];
				fd.fd1[1] = fd.fd2[1];
			}
			i++;
		}
		y++;
	}
	close_all(&fd);
	return (0);
}

int	wait_for_processes(int *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_pid;
	int	wait_ret;

	last_pid = -1;
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			wait_ret = waitpid(pids[i], &status, 0);
			if (wait_ret > 0)
			{
				if (WIFEXITED(status))
				{
					printf("Command %d (PID %d) exited with status %d\n", i,
						pids[i], WEXITSTATUS(status)); //debug
				}
				else if (WIFSIGNALED(status))
				{
					printf("Command %d (PID %d) was killed by signal %d\n", i, pids[i],
						WTERMSIG(status));
				}
				else
					printf("Command %d (PID %d) terminated abnormally\n", i, pids[i]);
				last_pid = pids[i];
			}
			else
				perror("waitpid failed");
		}
		i++;
	}
	return (last_pid);
}
