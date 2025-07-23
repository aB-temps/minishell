/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:50 by enzo              #+#    #+#             */
/*   Updated: 2025/07/23 17:13:20 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include <stdio.h>

int	free_child(t_exec *exec, t_input *input)
{
	free(exec->cmd_path);
	free(exec->pid_child);
	clear_vector(&input->v_tokens);
	ft_lstclear(&input->env->list, &clear_env_list_elem);
	free_tab_return_null(input->env->array);
	free(input->env);
	free(input->prompt);
	free(input);
	return (127);
}

static void	apply_redirections(t_input *input, int cmd_index, int *fd_infile,
		int *fd_outfile)
{
	t_token	*tokens_array;
	int		i;
	int		cmd_count;

	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	cmd_count = 0;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
		{
			if (cmd_count == cmd_index)
			{
				i++;
				while (i < input->token_qty && tokens_array[i].type != COMMAND)
				{
					if (tokens_array[i].type == REDIR_OUT)
					{
						*fd_outfile = open(tokens_array[i].formatted_content,
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
					}
					else if (tokens_array[i].type == APPEND)
					{
						*fd_outfile = open(tokens_array[i].formatted_content,
								O_WRONLY | O_CREAT | O_APPEND, 0644);
					}
					else if (tokens_array[i].type == REDIR_IN)
					{
						*fd_infile = open(tokens_array[i].formatted_content,
								O_RDONLY);
					}
					else if (tokens_array[i].type == HEREDOC)
					{
						fprintf(stderr,"heredoc reading fd = %d\n", ((int*)tokens_array[i].formatted_content)[1]);
						*fd_infile = ((int*)tokens_array[i].formatted_content)[1];
					}
					i++;
				}
				break ;
			}
			cmd_count++;
		}
		i++;
	}
}

static int	execute_child(t_exec *exec, t_fd *fd, int i, t_input *input)
{
	(void)fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(exec->cmd_path);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		apply_redirections(input, i, &exec->fd_infile, &exec->fd_outfile);
		prepare_pipe(exec, fd, i);
		fprintf(stderr, "infile = %d\noutfile = %d\n", exec->fd_infile, exec->fd_outfile);
		if (!exec->cmd_path)
			exit(free_child(exec, input));
		execve(exec->cmd_path, exec->args, input->env->array);
		exit(free_child(exec, input));
	}
	free(exec->cmd_path);
	return (pid);
}

int	execute_command(t_token *current_token, t_exec *exec, t_fd *fd, int i,
		t_input *input)
{
	int	pid;

	pid = 0;
	exec->args = (char **)(current_token->formatted_content);
	exec->cmd_path = find_full_command_path(exec->args[0], input->env->array);
	pid = execute_child(exec, fd, i, input);
	return (pid);
}
