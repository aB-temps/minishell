#include "debug.h"
#include "exec.h"
#include <errno.h>

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static int	execute_all_commands(t_input *input, t_exec *exec)
{
	t_token	*tokens_array;

	exec->cmd_count = count_cmd(input);
	exec->pid_child = ft_calloc(exec->cmd_count, sizeof(pid_t));
	if (!exec->pid_child)
		return (1);
	tokens_array = (t_token *)input->v_tokens->array;
	create_all_files(tokens_array, input->token_qty);
	launch_all_commands(input, exec);
	wait_childs(exec, input);
	free(exec->pid_child);
	return (0);
}

void	create_all_files(t_token *token_array, int token_qty)
{
	int	i;
	int	fd_temp;
	int	flags;

	i = 0;
	while (i < token_qty)
	{
		if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
		{
			if (token_array[i].formatted_content)
			{
				if (token_array[i].type == APPEND)
					flags = O_WRONLY | O_CREAT | O_APPEND;
				else if (token_array[i].type == REDIR_OUT)
					flags = O_WRONLY | O_CREAT | O_TRUNC;
				fd_temp = open(token_array[i].formatted_content, flags, 0644);
				if (fd_temp == -1)
					perror(token_array[i].formatted_content);
				else
					close(fd_temp);
			}
		}
		i++;
	}
}

void	start_exec(t_input *input)
{
	t_exec	exec;

	exec.cmd_path = NULL;
	exec.args = NULL;
	exec.infile = NULL;
	exec.outfile = NULL;
	if (execute_all_commands(input, &exec) == 1)
		exit_minishell(input, input->last_exit_status);
}
