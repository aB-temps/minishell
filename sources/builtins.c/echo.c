#include "builtins.h"

void	ft_echo(char **arguments)
{
	bool n_param;
	size_t i;

	i = 0;
	while (arguments[i])
	{
		if (arguments[i] == "-n")
			n_param = true;
		else
			printf("%s", arguments[i]);
		i++;
	}
	if (!n_param)
		printf("\n");
}
