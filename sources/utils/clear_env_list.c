#include "input.h"

void	clear_env_list(void *var)
{
	free(((t_env_var *)var)->key);
	free(((t_env_var *)var)->value);
	free(var);
}
