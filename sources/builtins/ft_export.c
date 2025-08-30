/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:06 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/30 16:06:41 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env_export_noarg(char **env)
{
	const size_t	size = ft_tablen(env);
	size_t			i;

	i = 0;
	while (i < size)
		printf("%s\n", env[i++]);
}

static void	clear_env_var(t_env_var *var, t_input *input, t_exec *exec)
{
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->value)
			free(var->value);
		free(var);
	}
	exit_minishell(input, exec, EXIT_FAILURE);
}

static t_env_var	*parse_assignation(char *arg, t_minishell *minishell)
{
	t_env_var	*var;

	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
	if (!ft_strchr(arg, '='))
	{
		var->key = ft_strdup(arg);
		if (!var->key)
			clear_env_var(var, minishell->input, minishell->exec);
		var->value = (void *)0;
	}
	else
	{
		var->key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
		if (!var->key)
			clear_env_var(var, minishell->input, minishell->exec);
		var->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (!var->value)
			clear_env_var(var, minishell->input, minishell->exec);
	}
	return (var);
}

static void	assign_var(t_list *existing_var, t_list **varlist_node,
		t_env_var *var, t_minishell *minishell)
{
	if (existing_var)
	{
		free(var->key);
		if (!var->value)
			free(var->value);
		else
		{
			free(((t_env_var *)existing_var->content)->value);
			((t_env_var *)existing_var->content)->value = var->value;
		}
		free(var);
	}
	else
	{
		*varlist_node = ft_lstnew(var);
		if (!(*varlist_node))
			clear_env_var(var, minishell->input, minishell->exec);
		ft_lstadd_back(&minishell->input->env->list, *varlist_node);
	}
}

int	ft_export(char **cmd_args, t_minishell *minishell)
{
	t_list		*varlist_node;
	t_list		*existing_var;
	t_env_var	*var;
	size_t		i;
	size_t		args;

	i = 1;
	args = ft_tablen(cmd_args) - 1;
	if (!args)
	{
		print_env_export_noarg(minishell->input->env->array);
		return (0);
	}
	while (i <= args)
	{
		if (is_valid_varname(cmd_args[i]))
		{
			var = parse_assignation(cmd_args[i], minishell);
			existing_var = find_env_var(var->key, minishell->input->env->list);
			assign_var(existing_var, &varlist_node, var, minishell);
		}
		i++;
	}
	update_env_array(minishell->input, minishell->exec);
	return (0);
}
