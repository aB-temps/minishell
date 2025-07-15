#ifndef BUILTINS_H
# define BUILTINS_H

# include "checking.h"
# include "input.h"
# include "utils.h"
# include <linux/limits.h>
# include <stdio.h>

void	ft_echo(char **arguments);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_exit(t_input *input, int exit_code);
char	**ft_export(char **env);
void	ft_unset(char **env);

#endif