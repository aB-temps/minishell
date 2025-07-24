#include "builtins.h"

void	ft_unset(char **cmd_args, t_input *input)
{
	size_t	args;
	size_t	i;
	t_list	*prev;
	t_list	*elem;

	i = 1;
	args = ft_tablen(cmd_args) - 1;
	while (i <= args)
	{
		elem = find_env_var(cmd_args[i++], input->env->list);
		prev = lstgetprev(input->env->list, elem);
		ft_lstdelone(prev, elem, &clear_env_list_elem);
	}
	update_env_array(input);
}
