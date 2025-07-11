#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include <stdio.h>
# include "utils.h"
# include "checking.h"

void	ft_echo(char **arguments);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **env);

#endif