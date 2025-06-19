#include "builtins.h"

void	ft_env(char **env)
{
	size_t i;

	i = 0;
	while (env[i])
		printf("%s", env[i++]);
}