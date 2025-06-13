#include "exec.h"

static int	execute_child(char *cmd_path, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		execve(cmd_path, args, env);
		perror("execve");
		exit(126);
	}
	return (pid);
}

static int	handle_command_not_found(char **args, char *cmd_path)
{
	if (!cmd_path)
	{
		ft_putstr_fd("command not found : ", 2);
		ft_putendl_fd(*args, 2);
		return (-1);
	}
	return (0);
}

int	execute_command(t_input *input, t_token *current_token, char **env, int i)
{
	char	*cmd_path;
	char	**args;
	int		pid;

	(void)i;
	(void)input;
	args = (char **)(current_token->formatted_content);
	cmd_path = find_full_command_path(*args, env);
	if (handle_command_not_found(args, cmd_path) == -1)
		return (-1);
	pid = execute_child(cmd_path, args, env);
	return (pid);
}
