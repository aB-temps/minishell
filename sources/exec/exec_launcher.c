#include "exec.h"

void	launch_all_commands(t_input *input, char **env, int *pids) //to be change after the parssing of Achille
{
	ssize_t	cmd_start;
	ssize_t	cmd_end;
	int		i;

	i = 0;
	cmd_start = find_next_command(input, 0);
	while (cmd_start != -1)
	{
		cmd_end = find_command_end(input, cmd_start);
		//printf("Lancement de la commande %d de %zd à %zd\n", i + 1, cmd_start,
		//	cmd_end); //debug
		pids[i] = execute_simple_command_async(input, env, cmd_start, cmd_end);
		if (pids[i] > 0)
			i++;
		cmd_start = find_next_command(input, cmd_end + 1);
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
			// if (WIFEXITED(status))
			// 	printf("Processus %d terminé avec le statut: %d\n", pids[j], //debug
			// 		WEXITSTATUS(status));
			// else
			// 	printf("Processus %d terminé anormalement\n", pids[j]); //debug
		}
		j++;
	}
}
