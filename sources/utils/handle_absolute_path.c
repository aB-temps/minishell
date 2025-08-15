/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_absolute_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:59:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 19:13:32 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "unistd.h"
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
