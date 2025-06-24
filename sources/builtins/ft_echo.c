#include "builtins.h"

void	ft_echo(char **arguments)
{
	const size_t	len = ft_tablen(arguments);
	bool			n_param;
	size_t			i;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(arguments[i], "-n", 1))
			n_param = true;
		else
			printf("%s", arguments[i]);
		if (i < len - 1)
			printf(" ");
		i++;
	}
	if (!n_param)
		printf("\n");
}
