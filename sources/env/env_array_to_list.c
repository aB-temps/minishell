/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:15:49 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:50:19 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "input.h"
#include "utils.h"

static void	*exit_env_a_to_l(t_env_var *var, t_list *l_env)
{
	clear_env_list_elem(var);
	return (ft_lstclear(&l_env, &clear_env_list_elem));
}

void	update_env_list(t_input *input, t_exec *exec)
{
	if (input->env->list)
		ft_lstclear(&input->env->list, &clear_env_list_elem);
	input->env->list = env_array_to_list(input->env->array);
	if (!input->env->list)
		exit_minishell(input, exec, EXIT_FAILURE);
}

t_list	*env_array_to_list(char **env)
{
	t_env_var	*env_var;
	t_list		*l_env;
	t_list		*element;
	size_t		i;

	i = 0;
	l_env = (void *)0;
	while (env[i])
	{
		env_var = ft_calloc(1, sizeof(t_env_var));
		if (!env_var)
			return (exit_env_a_to_l(env_var, l_env));
		env_var->key = ft_strndup(env[i], (size_t)(ft_strchr(env[i], '=') - env[i]));
		if (!env_var->key)
			return (exit_env_a_to_l(env_var, l_env));
		env_var->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_var->value)
			return (exit_env_a_to_l(env_var, l_env));
		element = ft_lstnew(env_var);
		if (!element)
			return (exit_env_a_to_l(env_var, l_env));
		ft_lstadd_back(&l_env, element);
		i++;
	}
	return (l_env);
}
