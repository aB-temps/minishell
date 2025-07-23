/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:45 by enzo              #+#    #+#             */
/*   Updated: 2025/07/22 22:35:19 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	create_all_files(exec, tokens_array, input->token_qty);
	launch_all_commands(input, exec);
	wait_childs(exec, input);
	free(exec->pid_child);
	return (0);
}

int	create_all_files(t_exec *exec, t_token *token_array, int token_qty)
{
    int	i;
    int	fd_temp;
    int	flags;

    i = 0;
    exec->fd_infile = -1;
    exec->fd_outfile = -1;
    while (i < token_qty)
    {
        if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
        {
            if (token_array[i].formatted_content)
            {
                flags = (token_array[i].type == APPEND) ? 
                    (O_WRONLY | O_CREAT | O_APPEND) : 
                    (O_WRONLY | O_CREAT | O_TRUNC);
                fd_temp = open(token_array[i].formatted_content, flags, 0644);
                if (fd_temp == -1)
                {
                    perror(token_array[i].formatted_content);
					return (1);
				}
                else
                {
                    if (exec->fd_outfile != -1)
                        close(exec->fd_outfile);
                    exec->fd_outfile = fd_temp;
                }
            }
        }
        else if (token_array[i].type == REDIR_IN)
        {
            if (token_array[i].formatted_content)
            {
                fd_temp = open(token_array[i].formatted_content, O_RDONLY);
                if (fd_temp == -1)
                {
                    perror(token_array[i].formatted_content);
					return (1);
				}
                else
                {
                    if (exec->fd_infile != -1)
                        close(exec->fd_infile);
                    exec->fd_infile = fd_temp;
                }
            }
        }
        i++;
    }
	return (0);
}

void	start_exec(t_input *input)
{
	t_exec	exec;

	exec.cmd_path = NULL;
	exec.args = NULL;
	exec.fd_infile = -1;
	exec.fd_outfile = -1;
	if (execute_all_commands(input, &exec) == 1)
		exit_minishell(input, input->last_exit_status);
}
