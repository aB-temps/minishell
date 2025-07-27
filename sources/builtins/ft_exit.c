#include "exec.h"
#include "input.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_numeric_error(char *arg, t_input *input, t_exec *exec)
{
	input->last_exit_status = 2;
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit_exec(input, exec);
}

void	ft_exit(char **cmd, t_input *input, t_exec *exec)
{
	int	nb;
	int	error;

	if (exec->cmd_count == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd[1])
	{
		exit_exec(input, exec);
		return ;
	}
	if (!is_valid_number(cmd[1]))
		print_numeric_error(cmd[1], input, exec);
	if (cmd[2])
	{
		input->last_exit_status = 1;
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	nb = ft_atoi(cmd[1], &error);
	input->last_exit_status = nb % 256;
	exit_exec(input, exec);
}
