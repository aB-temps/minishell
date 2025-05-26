#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

void	get_input(char **env)
{
	t_input input;
	char *line;
	char *prompt[_SC_LOGIN_NAME_MAX + PATH_MAX];

	init_input(&input);
	line = (void *)0;
	while (1)
	{
		build_prompt(prompt, env);
		line = readline(*prompt);
		free(line);
	}
}