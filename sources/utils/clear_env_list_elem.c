#include "input.h"
#include "stdio.h"

void	clear_env_list_elem(void *var)
{
	if (var)
	{
		if (((t_env_var *)var)->key)
			free(((t_env_var *)var)->key);
		if (((t_env_var *)var)->value)
			free(((t_env_var *)var)->value);
		free(var);
	}
}
