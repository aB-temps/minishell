#include "exec.h"

void handle_token(t_input *input, ssize_t i, char **env)
{
	if (input->token[i].type == COMMAND)
		printf("C'est une commande\n");
	else if (input->token[i].type == PIPE)
		printf("C'est une '|'\n");
}

void	exec_cmd(t_input *input, char **env)
{
	ssize_t i = 0;
	t_fd fd;
	

	printf("Nombre de token = %zd\n", input->token_qty);
	while (i < input->token_qty)
	{
		handle_token(input, i, env);
		i++;
	}
}
