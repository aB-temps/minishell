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

typedef struct s_fd
{
	int		fd1[2];
	int		fd2[2];
}			t_fd;

typedef struct s_data
{
	char	**av;
	int		ac;
	int		id;
	char	*infile;
	int		fd_infile;
	char	*outfile;
	int		fd_outfile;
	char	***args;
	char	**env;
	int		cmd_count;
	char	*path;
	int		count_path;
	char	**split_path;
	pid_t	*pid_children;
}			t_data;

/*------------------------------- FUNCTIONS -------------------------------*/
t_token		*get_token_at_index(t_vector *vec, size_t index);
char		*get_path(char **env);
void		cleanup_command_resources(char **args, char *cmd_path);
char		*find_command_path(char *cmd, char **paths);
char		*find_full_command_path(char *cmd, char **env);
int			execute_simple_command_async(t_input *input, char **env, int start_idx, int end_idx);
char		**build_args_array(t_input *input, int start_idx, int end_idx);
ssize_t		find_next_command(t_input *input, ssize_t start);
ssize_t		find_command_end(t_input *input, ssize_t start);
int			count_commands(t_input *input);
void		launch_all_commands(t_input *input, char **env, int *pids);
void		wait_for_processes(int *pids, int cmd_count);
void		debug_print_all_tokens(t_input *input, char **env);
void		debug_print_token(t_token *token);
void		handle_token(t_input *input, ssize_t i, char **env);
void		free_all(t_data *data);
int			ft_pipex(t_data *data, t_fd *fd);
void		count_args(t_data *data);
void		close_all(t_fd *fd);
void		first_cmd(t_fd *fd, char *file_name, t_data *data);
void		middle_cmd(t_fd *fd, t_data *data);
void		last_cmd(t_fd *fd, char *file_name, t_data *data);
int			wait_childs(t_data *data);
void		error_occured(t_fd *fd, t_data *data, char *error_msg);
void		exec_cmd(t_input *input, char **env);
void		free_input_content(t_input *input);

#endif
