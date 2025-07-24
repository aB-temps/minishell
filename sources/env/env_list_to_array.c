#include "debug.h"
#include "input.h"
#include "libft.h"
#include "utils.h"

void	update_env_array(t_input *input)
{
	if (input->env->array)
		free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input, EXIT_FAILURE);
}

char	**env_list_to_array(t_list *env)
{
	char	**a_env;
	size_t	i;
	size_t	len;

	i = 0;
	a_env = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!a_env)
		return ((void *)0);
	while (env)
	{
		len = ft_strlen(((t_env_var *)env->content)->key)
			+ ft_strlen(((t_env_var *)env->content)->value) + 2;
		a_env[i] = ft_calloc(len, sizeof(char));
		if (!a_env[i])
			return (free_tab_return_null(a_env));
		ft_strlcpy(a_env[i], ((t_env_var *)env->content)->key, len);
		if (((t_env_var *)env->content)->value)
		{
			ft_strlcat(a_env[i], "=", len);
			ft_strlcat(a_env[i], ((t_env_var *)env->content)->value, len);
		}
		env = env->next;
		i++;
	}
	a_env[i] = (void *)0;
	return (a_env);
}
