/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:03:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 18:34:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*-------------------------------- INCLUDES --------------------------------*/
# include "input.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*--------------------------------- ENUM ---------------------------------*/

enum			block_type
{
	NO_TYPE = -1,
	CMD_REDIR,
	CMD_NOREDIR,
	REDIR_NOCMD,
};

/*-------------------------------- STRUCTS --------------------------------*/

/*
BASH FORK lorsqu'il y a :
	- au moins 1 token commande (non builtin)
	- au moins 1 pipe

DONC BASH NE FORK PAS lorsqu'il y a :
	- une redir sans commande (non builtin) sans pipe
	- une commande (builtin) sans pipe
*/

typedef struct s_pipe_fds
{
	int			fd1[2];
	int			fd2[2];
}				t_pipe_fds;

typedef struct s_cmd
{
	char		*cmd_path;
	char		**cmd_args;
	bool		is_builtin;

}				t_cmd;

typedef struct s_block
{
	t_cmd		*cmd;
	int			io_fds[2];
}				t_block;

typedef struct s_exec
{
	pid_t		*pid_child;
	t_block		block;
	size_t		block_qty;
	t_pipe_fds	*pipe_fds;
	int			return_error;
}				t_exec;

/*-------------------------------- FUNCTIONS --------------------------------*/
void			start_exec(t_input *input);
bool			init_exec(t_exec **exec, t_input *input);
bool			exec_cmd(t_input *input, t_exec *exec, int *pid, size_t i);
bool			create_files_in_block(t_input *input, t_exec *exec,
					ssize_t cmd_nb);
void			free_cmd(t_cmd **cmd);
void			wait_child(t_exec *exec, int *exit_status);
bool			is_builtin(char *cmd);
bool			init_block_cmd(t_input *input, t_exec *exec, t_cmd **cmd,
					ssize_t *i);
void			prepare_pipes(t_input *input, t_exec *exec, size_t i);

#endif
