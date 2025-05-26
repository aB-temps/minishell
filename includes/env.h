#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include <linux/limits.h>
# include <unistd.h>

char	*get_line_in_env(char **env, char *to_find);

#endif