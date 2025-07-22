#include "builtins.h"
#include "debug.h"

static void	print_env_empty_export(char **env)
{
	const size_t	size = ft_tablen(env);
	size_t			i;

	i = 0;
	while (i < size)
		printf("export %s\n", env[i++]);
}

t_env_var	*parse_assignation(char *arg, t_input *input)
{
	t_env_var	*var;

	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		exit_minishell(input, EXIT_FAILURE);
	if (!ft_strchr(arg, '='))
	{
		var->key = ft_strdup(arg);
		if (!var->key)
		{
			free(var);
			exit_minishell(input, EXIT_FAILURE);
		}
		var->value = (void *)0;
	}
	else
	{
		var->key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
		if (!var->key)
		{
			free(var);
			exit_minishell(input, EXIT_FAILURE);
		}
		var->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (!var->value)
		{
			free(var->key);
			free(var);
			exit_minishell(input, EXIT_FAILURE);
		}
	}
	return (var);
}

void	ft_export(char **cmd_args, t_input *input)
{
	t_list		*varlist_node;
	t_list		*existing_var;
	t_env_var	*var;
	size_t		i;
	size_t		args;

	i = 1;
	args = ft_tablen(cmd_args) - 1;
	if (!args)
		return (print_env_empty_export(input->env->array));
	while (i <= args)
	{
		var = parse_assignation(cmd_args[i], input);
		existing_var = find_env_var(var->key, input->env->list);
		if (existing_var)
		{
			free(((t_env_var *)existing_var->content)->value);
			((t_env_var *)existing_var->content)->value = var->value;
		}
		else
		{
			varlist_node = ft_lstnew(var);
			if (!varlist_node)
				exit_minishell(input, EXIT_FAILURE);
			ft_lstadd_back(&input->env->list, varlist_node);
		}
		i++;
	}
	update_env_array(input);
}
