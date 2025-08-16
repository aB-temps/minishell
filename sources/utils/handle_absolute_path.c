/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:03:56 by enzo              #+#    #+#             */
/*   Updated: 2025/08/16 20:03:59 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>
#include <stdio.h>

char	*handle_absolute_path(t_exec *exec, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		exec->return_error = 126;
		perror(cmd);
		return (NULL);
	}
	exec->return_error = 127;
	perror(cmd);
	return (NULL);
}
