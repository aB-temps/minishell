/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:55:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 11:07:56 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"

pid_t	exec_cmd(t_input *input, t_exec *exec, t_block block)
{
	pid_t	pid;
	t_token	token_array;

	(void)block;
	(void)exec;
	(void)input;
	pid = fork();
	if (pid == -1)
	{
		perror(fork);
		return (-1);
	}
	if (pid == 0)
	{
		init_io_fds();
	}
	return (pid);
}
