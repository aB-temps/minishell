#include "builtins.h"
#include "debug.h"

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
	t_env_var	var;
	size_t		i;
	size_t		args;
	char		**tmp;

	i = 1;
	printf("DEBUG => export :\n");
	args = ft_tablen(cmd_args) - 1;
	printf("args_qty = %zu\n", args);
	if (!args)
		return (print_env_empty_export(input->env->array));
	while (i <= args)
	{
		if (!ft_strchr(cmd_args[i], '='))
		{
			var.key = ft_strdup(cmd_args[i]);
			if (!var.key)
				exit_minishell(input, EXIT_FAILURE);
			var.value = (void *)0;
		}
		else
		{
			var.key = ft_strndup(cmd_args[i], ft_strchr(cmd_args[i], '=')
					- cmd_args[i]);
			if (!var.key)
				exit_minishell(input, EXIT_FAILURE);
			var.value = ft_strdup(ft_strchr(cmd_args[i], '=') + 1);
			if (!var.value)
				exit_minishell(input, EXIT_FAILURE);
		}
		printf("var.key => %s\n", var.key);
		printf("var.value => %s\n\n", var.value);
		varlist_node = ft_lstnew(&var);
		if (!varlist_node)
			exit_minishell(input, EXIT_FAILURE);
		ft_lstadd_back(&input->env->list, varlist_node);
		i++;
	}
	tmp = input->env->array;
	input->env->array = env_list_to_array(input->env->list);
	free_tab_return_null(tmp);
	print_tab(cmd_args);
}
