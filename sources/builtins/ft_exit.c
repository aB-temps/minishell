#include "exec.h"
#include "input.h"

void	ft_exit(t_input *input, t_exec *exec, int exit_code)
{
	exit_exec(exit_code, exec, input);
}
