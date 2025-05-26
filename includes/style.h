#ifndef STYLE_H
# define STYLE_H

# include "libft.h"
# include "text_formatting.h"
# include <linux/limits.h>
# include <stdio.h>
# include <unistd.h>

void	welcome(void);
void	build_prompt(char *prompt[_SC_LOGIN_NAME_MAX + PATH_MAX], char **env);

#endif