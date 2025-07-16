#include "input.h"
#include "libft.h"
#include "utils.h"

void	clear_envlist(void *env_var)
{
	free(((t_env_var *)env_var)->key);
	free(((t_env_var *)env_var)->value);
	free(env_var);
}

t_list	*env_array_to_list(char **env)
{
	t_env_var	*env_var;
	t_list		*l_env;
	t_list		*element;
	size_t		i;

	i = 0;
	l_env = (void *)0;
	while (env[i])
	{
		env_var = ft_calloc(1, sizeof(t_env_var));
		if (!env_var)
			return (ft_lstclear(&l_env, &clear_envlist), (void *)0);
		env_var->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!env_var->key)
			return (ft_lstclear(&l_env, &clear_envlist), (void *)0);
		env_var->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_var->value)
			return (ft_lstclear(&l_env, &clear_envlist), (void *)0);
		element = ft_lstnew(env_var);
		ft_lstadd_back(&l_env, element);
		i++;
	}
	return (l_env);
}
