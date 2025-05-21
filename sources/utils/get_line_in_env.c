#include "env.h"

char	*get_line_in_env(char **env, char *to_find)
{
	char *line;
	int i;
	size_t len;

	i = 0;
	line = NULL;
	len = ft_strlen(to_find);
	while (env[i] && !line)
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
		{
			line = env[i] + len;
			break ;
		}
		i++;
	}
	if (!line || ft_strlen(line) == 0)
		line = ".";
	return (line);
}
