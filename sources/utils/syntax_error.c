#include "input.h"
#include <unistd.h>

void	syntax_error(t_input *input)
{
	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
}