/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:15:49 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 18:15:52 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "utils.h"

void	update_env_list(t_input *input)
{
	if (input->env->list)
		ft_lstclear(&input->env->list, &clear_env_list_elem);
	input->env->list = env_array_to_list(input->env->array);
	if (!input->env->list)
		exit_minishell(input, EXIT_FAILURE);
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
			return (ft_lstclear(&l_env, &clear_env_list_elem), (void *)0);
		env_var->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!env_var->key)
			return (ft_lstclear(&l_env, &clear_env_list_elem), (void *)0);
		env_var->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_var->value)
			return (ft_lstclear(&l_env, &clear_env_list_elem), (void *)0);
		element = ft_lstnew(env_var);
		if (!element)
			return (ft_lstclear(&l_env, &clear_env_list_elem), (void *)0);
		ft_lstadd_back(&l_env, element);
		i++;
	}
	return (l_env);
}
