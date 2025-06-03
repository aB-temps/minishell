#include "exec.h"

static int	execute_child_process_async(char *cmd_path, char **args, char **env)
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
		dprintf(STDERR_FILENO, "Command not found: %s\n", args[0]); // FAIRE NOUS MEME LE DPRINTF ?
		free(args);
		return (-1);
	}
	return (0);
}

int	execute_simple_command_async(t_input *input, char **env, int start_idx,
		int end_idx)
{
	char	**args;
	char	*cmd_path;
	int		pid;

	args = build_args_array(input, start_idx, end_idx);
	if (!args)
		return (-1);
	if (!args[0])
	{
		free(args);
		return (0);
	}
	cmd_path = find_full_command_path(args[0], env);
	printf("Command path = '%s'\n", cmd_path); // debug
	if (handle_command_not_found(args, cmd_path) == -1)
		return (-1);
	pid = execute_child_process_async(cmd_path, args, env);
	cleanup_command_resources(args, cmd_path);
	return (pid);
}
