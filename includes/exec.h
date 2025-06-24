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
	int	fd1[2];
	int	fd2[2];
}		t_fd;

/*------------------------------- FUNCTIONS -------------------------------*/
char	*get_path(char **env);
void	cleanup_command_resources(char **args, char *cmd_path);
char	*find_command_path(char *cmd, char **paths);
char	*find_full_command_path(char *cmd, char **env);
int		execute_command(t_token *current_token, char **env);
void	launch_all_commands(t_input *input, char **env, int *pids);
void	wait_for_processes(int *pids, int cmd_count);
int		exec_cmd(t_input *input, char **env);
int		count_cmd(t_input *input);

#endif
