#include "exec.h"

int	launch_all_commands(t_input *input, t_exec *exec)
{
	t_token	*current_token;
	t_token	*tokens_array;
	t_fd	fd;
	int		i;
	int		y;

	y = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	init_fd(&fd);
	while (i < exec->cmd_count)
	{
		current_token = &tokens_array[y];
		if (current_token->type == COMMAND)
		{
			if (i < exec->cmd_count - 1)
			{
				if (pipe(fd.fd2) == -1)
				{
					close_all(&fd);
					return (1);
				}
			}
			if (!is_builtin(*current_token, input, exec, &fd, i))
			{
				exec->pid_child[i] = execute_command(current_token, exec,
						&fd, i, input);
			}
			if (i > 0)
				close(fd.fd1[0]);
			if (i < exec->cmd_count - 1)
				close(fd.fd2[1]);
			if (i < exec->cmd_count - 1)
			{
				close(fd.fd2[1]);
				fd.fd1[0] = fd.fd2[0];
				fd.fd1[1] = fd.fd2[1];
			}
			i++;
		}
		y++;
	}
	close_all(&fd);
	return (0);
}

static void	check_cmd(t_input *input, t_token *tokens_array, int i)
{
	char	*cmd;

	cmd = get_cmd_by_index(input, tokens_array, i);
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
	t_token	*current_token;

	status = 0;
	current_token = &tokens_array[i];
	waitpid(exec->pid_child[i], &status, 0);
	if (WIFEXITED(status))
	{
		input->last_exit_status = WEXITSTATUS(status);
		if (input->last_exit_status == 127)
			check_cmd(input, tokens_array, i);
		else if (input->last_exit_status == 126)
			if (errno != 0)
				perror(((char **)current_token->formatted_content)[0]);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		input->last_exit_status = 128 + sig;
		if (sig == SIGTERM)
			ft_putendl_fd("Terminated", 2);
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
