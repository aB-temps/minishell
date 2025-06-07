#include "input.h"

void	exit_minishell(t_input *input, int exit_code)
{
	clear_vector(input->v_tokens);
	free(input->line);
	free(input->prompt);
	free(input);
	exit(exit_code);
}