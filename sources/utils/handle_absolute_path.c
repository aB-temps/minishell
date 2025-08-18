/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:03:56 by enzo              #+#    #+#             */
/*   Updated: 2025/08/18 05:20:35 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>
#include <unistd.h>

char	*handle_absolute_path(t_exec *exec, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		exec->return_error = 126;
		return (ft_strdup(cmd));
	}
	exec->return_error = 127;
	return (NULL);
}
