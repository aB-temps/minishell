#include "exec.h"
#include "input.h"

void	ft_exit(t_input *input, t_exec *exec)
{
	if (exec->cmd_count == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	exit_exec(input, exec);
}
