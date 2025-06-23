#include "builtins.h"

bool	is_valid_echo_param(char c)
{
	const char	valid_params[3] = {'e', 'E', 'n'};
	size_t		i;

	i = 0;
	while (i < 3)
	{
		if (c == valid_params[i])
			return (true);
		else
			i++;
	}
	return (false);
}

void	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	bool			n_param;
	size_t			i;

	i = 1;
	n_param = false;
	while (i < args_qty)
	{
		printf("%s", args[i]);
		if (i < args_qty - 1)
			printf(" ");
		i++;
	}
	if (!n_param)
		printf("\n");
}
