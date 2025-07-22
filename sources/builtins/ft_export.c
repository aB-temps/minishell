#include "builtins.h"
#include "debug.h"

void	print_env_list(t_list *l_env)
{
	while (l_env)
	{
		printf("key -> %s\n", ((t_env_var *)l_env->content)->key);
		printf("value -> %s\n", ((t_env_var *)l_env->content)->value);
		l_env = l_env->next;
	}
}

void	print_env_empty_export(char **env)
{
	const size_t	size = ft_tablen(env);
	size_t			i;

	i = 0;
	while (i < size)
		printf("export %s\n", env[i++]);
}

void	ft_export(char **cmd_args, t_input *input)
{
	t_list		*varlist_node;
	t_env_var	*var;
	size_t		i;
	size_t		args;

	i = 1;
	args = ft_tablen(cmd_args) - 1;
	if (!args)
		return (print_env_empty_export(input->env->array));
	while (i <= args)
	{
		var = ft_calloc(1, sizeof(t_env_var));
		if (!var)
			exit_minishell(input, EXIT_FAILURE);
		if (!ft_strchr(cmd_args[i], '='))
		{
			var->key = ft_strdup(cmd_args[i]);
			if (!var->key)
				exit_minishell(input, EXIT_FAILURE);
			var->value = (void *)0;
		}
		else
		{
			var->key = ft_strndup(cmd_args[i], ft_strchr(cmd_args[i], '=')
					- cmd_args[i] - 1);
			if (!var->key)
				exit_minishell(input, EXIT_FAILURE);
			var->value = ft_strdup(ft_strchr(cmd_args[i], '=') + 1);
			if (!var->value)
				exit_minishell(input, EXIT_FAILURE);
		}
		varlist_node = ft_lstnew(var);
		if (!varlist_node)
			exit_minishell(input, EXIT_FAILURE);
		ft_lstadd_back(&input->env->list, varlist_node);
		i++;
	}
	free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input, EXIT_FAILURE);
	// DEBUGGGGG
	// print_tab(cmd_args);
	// print_env_list(input->env->list);
	// DEBUGGGGG
}
