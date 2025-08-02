/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:15:46 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 14:20:51 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "input.h"
#include "libft.h"
#include "utils.h"
#include "builtins.h"

void	update_env_array(t_input *input, t_exec*exec)
{
	if (input->env->array)
		free_tab_return_null(input->env->array);
	input->env->array = env_list_to_array(input->env->list);
	if (!input->env->array)
		exit_minishell(input,exec, EXIT_FAILURE);
}

static void	cpy_var_value(char *value, char **var, size_t line_len)
{
	ft_strlcat(*var, "=", line_len);
	ft_strlcat(*var, value, line_len);
}

char	**env_list_to_array(t_list *env)
{
	char	**a_env;
	size_t	i;
	size_t	len;

	i = 0;
	a_env = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!a_env)
		return ((void *)0);
	while (env)
	{
		len = ft_strlen(((t_env_var *)env->content)->key)
			+ ft_strlen(((t_env_var *)env->content)->value) + 2;
		a_env[i] = ft_calloc(len, sizeof(char));
		if (!a_env[i])
			return (free_tab_return_null(a_env));
		ft_strlcpy(a_env[i], ((t_env_var *)env->content)->key, len);
		if (((t_env_var *)env->content)->value)
			cpy_var_value(((t_env_var *)env->content)->value, &a_env[i], len);
		env = env->next;
		i++;
	}
	a_env[i] = (void *)0;
	return (a_env);
}
