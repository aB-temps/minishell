#include "builtins.h"
#include "debug.h"

t_list	*find_env_var(char *key, t_list *env)
{
	size_t i;

	i = 0;
	while (env)
	{
		printf("'%s' vs '%s' => ", key, ((t_env_var *)env->content)->key);
		if (!ft_strcmp(key, ((t_env_var *)env->content)->key))
		{
			printf("%smatch\n%s", FG_GREEN, R_ALL);
			printf("\n%sexists%s\n\n", FG_GREEN BOLD, R_ALL);
			return (env);
		}
		else
			printf("%sdo not match%s\n", FG_RED, R_ALL);
		env = env->next;
	}
	printf("\n%sdo not exists%s\n\n", FG_RED BOLD, R_ALL);
	return ((void *)0);
}
