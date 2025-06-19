#include "builtins.h"

void	ft_echo(char **arguments)
{
	const size_t	len = tablen(arguments);
	bool			n_param;
	size_t			i;

	i = 0;
	while (i < ft_tablen)
	{
		if (arguments[i] == "-n")
			n_param = true;
		else
			printf("%s", arguments[i]);
		if (i < tablen - 1)
			printf(" ");
		i++;
	}
	if (!n_param)
		printf("\n");
}
