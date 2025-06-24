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
