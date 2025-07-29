/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sig_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:01:55 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/29 03:02:10 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_sig(t_exec *exec, t_token *tokens_array, t_input *input,
		int i)
{
	int		sig;
	int		status;
	t_token	*cur_token;

	status = 0;
	cur_token = &tokens_array[i];
	waitpid(exec->pid_child[i], &status, 0);
	if (WIFEXITED(status))
	{
		input->last_exit_status = WEXITSTATUS(status);
		if (input->last_exit_status == 127)
			check_cmd(input, tokens_array, i);
		else if (input->last_exit_status == 126)
		{
			if (errno != 0)
				perror(((char **)cur_token->formatted_content)[0]);
		}
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		input->last_exit_status = 128 + sig;
	}
}
