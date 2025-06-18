#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include "utils.h"

void	ft_echo(char **arguments);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **env);

#endif