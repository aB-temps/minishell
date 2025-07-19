#include "input.h"

char	*get_env_var(char *var_name, t_input *input)
{
	char *var_value;
	t_list *tmp;

	var_value = (void *)0;
	tmp = input->env->list;
	while (tmp)
	{
		if (!ft_strncmp(var_name, ((t_env_var *)tmp->content)->key,
				ft_strlen(var_name)
				+ ft_strlen(((t_env_var *)tmp->content)->key)))
			return ((((t_env_var *)tmp->content)->value));
		tmp = tmp->next;
	}
	var_value = ft_strdup("");
	if (!var_value)
		exit_minishell(input, EXIT_FAILURE);
	return (var_value);
}