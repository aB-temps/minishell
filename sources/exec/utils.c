#include "builtins.h"
#include "exec.h"
#include "input.h"

char	*get_type(ssize_t type)
{
	const char *types[11] = {
		"COMMAND",
		"ARG",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"ASSIGN",
		"S_QUOTES",
		"D_QUOTES",
		"ENV_VAR",
	};
	return ((char *)types[type]);
}

void	exit_exec(t_input *input, t_exec *exec, t_fd *fd)
{
	close_all(fd);
	free(exec->pid_child);
	exit_minishell(input, input->last_exit_status);
}

static void	execute_builtin(char **cmd, t_input *input, t_exec *exec, t_fd *fd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1]);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(input->env->array);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(input->env->array);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(input->env->array);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(input, exec, fd);
}

int	is_builtin(t_token current_token, t_input *input, t_exec *exec, t_fd *fd, int i)
{
	char	**cmd;
	int		pid;

	cmd = ((char **)current_token.formatted_content);
	if (!cmd || !cmd[0])
		return (0);

	if (ft_strcmp(cmd[0], "echo") && ft_strcmp(cmd[0], "pwd") && 
		ft_strcmp(cmd[0], "cd") && ft_strcmp(cmd[0], "export") && 
		ft_strcmp(cmd[0], "unset") && ft_strcmp(cmd[0], "env") && 
		ft_strcmp(cmd[0], "exit"))
		return (0);  // Pas un builtin

	if (exec->cmd_count > 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
		{
			prepare_pipe(exec, fd, i);
			execute_builtin(cmd, input, exec, fd);
			exit(0);
		}
		return (pid);
	}
	else
	{
		execute_builtin(cmd, input, exec, fd);
		return (1);
	}
}



char	*get_cmd_by_index(t_input *input, t_token *tokens_array, int index)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = 0;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		if (cmd_count - 1 == index)
			return (((char **)tokens_array[i].formatted_content)[0]);
		i++;
	}
	return (NULL);
}

int	count_cmd(t_input *input)
{
	int		i;
	int		cmd_count;
	t_token	*tokens_array;

	i = 0;
	cmd_count = 0;
	tokens_array = (t_token *)input->v_tokens->array;
	while (i < input->token_qty)
	{
		if (tokens_array[i].type == COMMAND)
			cmd_count++;
		i++;
	}
	return (cmd_count);
}
