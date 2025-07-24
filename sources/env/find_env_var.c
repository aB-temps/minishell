#include "builtins.h"
#include "debug.h"

t_list	*find_env_var(char *key, t_list *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(key, ((t_env_var *)env->content)->key))
			return (env);
	}
	env = env->next;
	return ((void *)0);
}
