#include "parsing.h"

void	get_input(char **env)
{
	char	*prompt;
	char	*line;

	prompt = NULL;
	line = NULL;
	while (1)
	{
		prompt = build_prompt(get_line_in_env(env, "USER="));
		if (!prompt)
			exit(EXIT_FAILURE);
		line = readline(prompt);
		free(line);
		free(prompt);
	}
}
