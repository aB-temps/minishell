/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:48 by enzo              #+#    #+#             */
/*   Updated: 2025/07/27 03:07:09 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"

static void	close_and_swap(t_exec *exec)
{
	if (exec->fd->fd1[0] != -1)
		close(exec->fd->fd1[0]);
	if (exec->fd->fd2[1] != -1)
		close(exec->fd->fd2[1]);
	exec->fd->fd1[0] = exec->fd->fd2[0];
	exec->fd->fd1[1] = exec->fd->fd2[1];
}

int	launch_all_commands(t_input *input, t_exec *exec)
{
	t_token	*cur_token;
	t_token	*tokens_array;
	int		i;
	int		y;

	tokens_array = (t_token *)input->v_tokens->array;
	y = 0;
	i = 0;
	while (y < input->token_qty && i < exec->cmd_count)
	{
		cur_token = &tokens_array[y];
		if (cur_token->type == COMMAND)
		{
			if (pipe(exec->fd->fd2) == -1)
				return (close_all(exec));
			exec->pid_child[i] = is_builtin(*cur_token, input, exec, i);
			if (exec->pid_child[i] == 0)
				exec->pid_child[i] = execute_command(cur_token, exec, i, input);
			if (i++ < exec->cmd_count - 1)
				close_and_swap(exec);
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
