#ifndef BUILTINS_H
# define BUILTINS_H

# include "checking.h"
# include "exec.h"
# include "input.h"
# include "utils.h"
# include <linux/limits.h>
# include <stdio.h>

void	ft_echo(char **arguments);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_exit(t_input *input, t_exec *exec, t_fd *fd);
void	ft_export(char **cmd_args, t_input *input);
void	ft_unset(char **env);

#endif