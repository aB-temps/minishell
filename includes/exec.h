/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:03:10 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/27 15:52:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*-------------------------------- INCLUDES --------------------------------*/
# include "input.h"

typedef struct s_minishell	t_minishell;

/*-------------------------------- STRUCTS --------------------------------*/

typedef struct s_pipe_fds
{
	int						fd1[2];
	int						fd2[2];
}							t_pipe_fds;

typedef struct s_cmd
{
	char					*cmd_path;
	char					**cmd_args;
	enum e_bool				is_builtin;

}							t_cmd;

typedef struct s_block
{
	t_cmd					*cmd;
	int						io_fds[2];
}							t_block;

typedef struct s_exec
{
	pid_t					*pid_child;
	t_block					block;
	size_t					block_qty;
	t_pipe_fds				*pipe_fds;
	int						return_error;
}							t_exec;

/*-------------------------------- FUNCTIONS --------------------------------*/
void						start_exec(t_input *input);
enum e_bool					init_exec(t_exec **exec, t_input *input);
enum e_bool					exec_cmd(t_input *input, t_exec *exec, int *pid,
								size_t i);
enum e_bool					create_files_in_block(t_input *input, t_exec *exec,
								ssize_t cmd_nb);
void						free_cmd(t_cmd **cmd);
void						wait_child(t_exec *exec, int *exit_status);
enum e_bool					is_builtin(char *cmd);
enum e_bool					init_block_cmd(t_input *input, t_exec *exec,
								t_cmd **cmd, ssize_t *i);
void						prepare_redir(t_input *input, t_exec *exec,
								size_t i);
int							handle_builtin(t_input *input, t_exec *exec,
								int *pid_child, int i);
int							apply_redirections_builtin(t_minishell *minishell,
								int *old_stdout, int *old_stdin, int i);
void						restore_redirections_builtin(t_input *input,
								t_exec *exec, int old_stdout, int old_stdin);
void						close_all_hd(t_input *input);

#endif
