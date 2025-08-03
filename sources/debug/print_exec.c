/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:33:44 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/24 15:55:09 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include <stdio.h>

void	print_exec(t_exec *exec, const char *stage)
{
	int	i;

	printf("================ [DEBUG T_EXEC] ================\n");
	printf("%s%s%s\n\n", UNDL, stage, R_ALL);
	if (!exec)
	{
		printf("t_exec est NULL\n");
		printf("============================================\n\n");
		return ;
	}
	printf("cmd_count: %s%d%s\n", BOLD, exec->cmd_count, R_ALL);
	printf("fd_infile: %s%d%s\n", BOLD, exec->fd_infile, R_ALL);
	printf("fd_outfile: %s%d%s\n", BOLD, exec->fd_outfile, R_ALL);
	if (exec->pid_child)
	{
		i = 0;
		while (i < exec->cmd_count)
		{
			printf("pid_child[%d]: %s%d%s\n", i, BOLD, exec->pid_child[i],
				R_ALL);
			i++;
		}
	}
	else
		printf("pid_child: %sNULL%s\n", BOLD, R_ALL);
	if (exec->fd)
	{
		printf("fd->fd1[0]: %s%d%s, fd->fd1[1]: %s%d%s\n", BOLD,
			exec->fd->fd1[0], R_ALL, BOLD, exec->fd->fd1[1], R_ALL);
		printf("fd->fd2[0]: %s%d%s, fd->fd2[1]: %s%d%s\n", BOLD,
			exec->fd->fd2[0], R_ALL, BOLD, exec->fd->fd2[1], R_ALL);
	}
	else
		printf("exec->fd: %sNULL%s\n", BOLD, R_ALL);
}
