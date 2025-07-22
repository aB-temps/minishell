#include "debug.h"
#include "input.h"
#include "libft.h"
#include "utils.h"

void	update_env_array(t_input *input)
{
	free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input, EXIT_FAILURE);
}

char	**env_list_to_array(t_list *env)
{
	char	**a_env;
	t_list	*tmp;
	size_t	i;
	size_t	len;

	tmp = env;
	i = 0;
	a_env = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!a_env)
		return ((void *)0);
	while (tmp)
	{
		len = ft_strlen(((t_env_var *)tmp->content)->key)
			+ ft_strlen(((t_env_var *)tmp->content)->value) + 2;
		a_env[i] = ft_calloc(len, sizeof(char));
		if (!a_env[i])
			return (free_tab_return_null(a_env));
		ft_strlcpy(a_env[i], ((t_env_var *)tmp->content)->key, len);
		if (((t_env_var *)tmp->content)->value)
		{
			ft_strlcat(a_env[i], "=", len);
			ft_strlcat(a_env[i], ((t_env_var *)tmp->content)->value, len);
		}
		tmp = tmp->next;
		i++;
	}
	a_env[i] = (void *)0;
	return (a_env);
}
