/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:15 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/30 04:05:47 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(char **cmd_args, t_input *input)
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
	}
	if (!prev && elem)
	{
		input->env->list = elem->next;
		clear_env_list_elem(elem->content);
		free(elem);
	}
	else if (elem)
		ft_lstdelone(prev, elem, &clear_env_list_elem);
	update_env_array(input);
	return (0);
}
