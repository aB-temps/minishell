#include "builtins.h"

t_list	*lstget_prev(t_list *lst, t_list *elem)
{
	t_list	*prev;

	prev = (void *)0;
	while (lst)
	{
		if (lst == elem)
			return (prev);
		prev = lst;
		lst = lst->next;
	}
	return ((void *)0);
}

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
		prev = lstget_prev(input->env->list, elem);
		ft_lstdelone(prev, elem, &clear_env_list_elem);
	}
	free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input, EXIT_FAILURE);
}
