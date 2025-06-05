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
		dprintf(STDERR_FILENO, "Command not found: %s\n", args[0]);
			// FAIRE NOUS MEME LE DPRINTF ?
		free(args);
		return (-1);
	}
	return (0);
}

int	execute_command(t_token *current_token, char **env)
{
	char	*cmd_path;
	char	**args;
	int		pid;

	args = (char **)(current_token->formatted_content);
	cmd_path = find_full_command_path(*args, env);
	dprintf(2,"Command path = '%s'\n", cmd_path); // debug
	if (handle_command_not_found(args, cmd_path) == -1)
		return (-1);
	pid = execute_child(cmd_path, args, env);
	cleanup_command_resources(args, cmd_path);
	return (pid);
}
