#ifndef BUILTINS_H
# define BUILTINS_H

# include "input.h"
# include <linux/limits.h>
# include <stdio.h>
# include <unistd.h>

void	ft_echo(char **arguments);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **env);

#endif