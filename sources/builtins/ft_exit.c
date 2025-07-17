#include "exec.h"
#include "input.h"

void	ft_exit(t_input *input, t_exec *exec, t_fd *fd)
{
	if (exec->cmd_count == 1)
		printf("exit\n");
	exit_exec(input, exec, fd);
}
