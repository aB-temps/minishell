#ifndef PIPEX_H
# define PIPEX_H

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
# include <time.h>
# include <unistd.h>

/*-------------------------------- DEFINES --------------------------------*/

/*--------------------------------- ENUM ---------------------------------*/

/*-------------------------------- STRUCTS --------------------------------*/

typedef struct s_exec
{
	char	*infile;
	char	*outfile;
	pid_t	*pid_children;
	char	**env;
	int		cmd_count;
	char	*cmd_path;
	char	**args;
}			t_exec;

typedef struct s_fd
{
	int		fd1[2];
	int		fd2[2];
}			t_fd;

/*------------------------------- FUNCTIONS -------------------------------*/
char		*get_path(char **env);
char		*find_command_path(char *cmd, char **paths);
char		*find_full_command_path(char *cmd, char **env);
int			execute_command(t_token *current_token, t_exec *exec, t_fd *fd,
				int i);
int			launch_all_commands(t_input *input, t_exec *exec);
int			exec_cmd(t_input *input, char **env, int *last_exit_status);
int			count_cmd(t_input *input);
void		wait_childs(t_exec *exec, t_input *input, int *exit_code);
void		close_all(t_fd *fd);
void		init_fd(t_fd *fd);
void		prepare_pipe(t_exec *exec, t_fd *fd, int i);
char		*get_cmd_by_index(t_input *input, t_token *tokens_array, int index);
int			is_builtin(t_token current_token);
#endif
