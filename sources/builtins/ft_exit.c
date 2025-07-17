#include "exec.h"
#include "input.h"

void	ft_exit(t_input *input, t_exec *exec, t_fd *fd)
{
	if (exec->cmd_count == 1)
		ft_putendl_fd("exit", 2);
	exit_exec(input, exec, fd);
}
