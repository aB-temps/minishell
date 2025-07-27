/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:09:29 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/27 18:10:28 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error_occured(t_exec *exec, char *error_msg)
{
	perror(error_msg);
	close_all(exec);
	exit(1);
}

void	check_cmd(t_input *input, t_token *tokens_array, int i)
{
	char	*cmd;

	cmd = get_cmd_by_index(input, tokens_array, i);
	if (check_builtin(cmd) == 1)
		return ;
	if (!cmd)
		ft_putendl_fd(": command not found", 2);
	else if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) != 0)
		{
			perror(cmd);
			return ;
		}
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
}
