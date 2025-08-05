/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:55:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/05 18:55:33 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "input.h"
#include "utils.h"

pid_t	exec_cmd(t_input *input, t_exec *exec, t_block block, size_t i)
{
	pid_t	pid;

	pid = 0;
	(void)block;
	(void)input;
	(void)i;
	print_exec(exec, "INSIDE exec_cmd");
	pid = fork();
	if (pid == -1)
	{
		free_and_close_exec(&exec);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		create_files_in_block(input, exec, i);
		print_exec(exec, "INSIDE CHILD");
		free_and_close_exec(&exec);
		exit(133);
	}
	return (pid);
}
