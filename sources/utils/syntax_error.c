#include "input.h"
#include <unistd.h>

// Remake an atomic dprintf ?

void	syntax_error(t_input *input, char* s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	exit_minishell(input, 2);
}