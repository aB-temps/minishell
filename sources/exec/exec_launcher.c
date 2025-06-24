#include "exec.h"

static int	has_pipes(t_input *input)
{
	int		i;
	t_token	*tokens_array;

	i = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == PIPE)
			return (1);
		i++;
	}
	return (0);
}

void	launch_all_commands(t_input *input, char **env, int *pids)
{
	int		as_pipes;
	t_token	*current_token;
	t_token	*tokens_array;

	as_pipes = has_pipes(input);
	if (as_pipes)
	{
		printf("Pipes détectés - pas encore implémenté\n");
	}
	else
	{
		tokens_array = (t_token *)input->v_tokens->array;
		current_token = &tokens_array[0];
		pids[0] = execute_command(current_token, env);
	}
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
					printf("Command %d (PID %d) exited with status %d\n",
						j, pids[j], WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					printf("Command %d was killed by signal %d\n",
						j, WTERMSIG(status));
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
