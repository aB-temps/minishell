#include "exec.h"

void	launch_all_commands(t_input *input, char **env, int *pids)
{
	int		i;
	int		y;
	t_token	*current_token;
	t_token	*tokens_array;

	y = 0;
	i = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	while (i <= input->token_qty - 1)
	{
		current_token = &tokens_array[i];
		if (current_token->type == COMMAND)
			pids[y++] = execute_command(current_token, env);
		i++;
	}
}

void	wait_for_processes(int *pids, int cmd_count)
{
	int	j;
	int	status;

	j = 0;
	while (j < cmd_count)
	{
		if (pids[j] > 0)
		{
			waitpid(pids[j], &status, 0);
			if (WIFEXITED(status))
				printf("Processus %d terminé avec le statut: %d\n", pids[j],
					WEXITSTATUS(status));
			else
				printf("Processus %d terminé anormalement\n", pids[j]); // debug
		}
		j++;
	}
}
