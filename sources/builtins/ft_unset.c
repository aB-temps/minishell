#include "builtins.h"

void	ft_unset(char **cmd_args, t_input *input)
{
	size_t	args;
	size_t	i;

	i = 1;
	args = ft_tablen(cmd_args) - 1;
	while (i <= args)
		ft_lstdelone(find_env_var(cmd_args[i++], input->env->list));
	free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input, EXIT_FAILURE);
}
