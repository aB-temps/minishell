#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

void	get_input(char **env)
{
	(void)env;
	t_input input;
	char *line;
	char *prompt;

	init_input(&input);
	line = (void *)0;
	for (int i = 0; i < 5; i++)
	{
		prompt = (void *)0;
		build_prompt(&prompt);
		line = readline(prompt);
		free(line);
		free(prompt);
	}
}