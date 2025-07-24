/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:48 by enzo              #+#    #+#             */
/*   Updated: 2025/07/24 12:57:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"

int	launch_all_commands(t_input *input, t_exec *exec)
{
	t_token	*cur_token;
	t_token	*tokens_array;
	int		i;
	int		y;

	y = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	while (y < input->token_qty && i < exec->cmd_count)
	{
		print_exec(exec, "INSIDE_EXEC");
		cur_token = &tokens_array[y];
		if (cur_token->type == COMMAND)
		{
			if (i < exec->cmd_count - 1)
			{
				if (pipe(exec->fd->fd2) == -1)
				{
					close_all(exec);
					return (1);
				}
			}
			exec->pid_child[i] = is_builtin(*cur_token, input, exec, i);
			if (exec->pid_child[i] == 0)
			{
				exec->pid_child[i] = execute_command(cur_token, exec, i, input);
			}
			if (i > 0)
				close(exec->fd->fd1[0]);
			if (i < exec->cmd_count - 1)
				close(exec->fd->fd2[1]);
			if (i < exec->cmd_count - 1)
			{
				exec->fd->fd1[0] = exec->fd->fd2[0];
				exec->fd->fd1[1] = exec->fd->fd2[1];
			}
			i++;
		}
		y++;
	}
	close_all(exec);
	return (0);
}

static void	check_cmd(t_input *input, t_token *tokens_array, int i)
{
	char	*cmd;

	cmd = get_cmd_by_index(input, tokens_array, i);
	if (check_builtin(cmd) == 1)
		return ;
	if (!cmd)
		ft_putendl_fd(": command not found", 2);
	else if (ft_strchr(cmd, '/') != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

static void	check_sig(t_exec *exec, t_token *tokens_array, t_input *input,
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
		input->last_exit_status = 128 + sig;
	}
}

void	wait_childs(t_exec *exec, t_input *input)
{
	int		i;
	t_token	*tokens_array;

	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < exec->cmd_count)
		check_sig(exec, tokens_array, input, i++);
}
