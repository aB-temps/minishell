#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	welcome(void);
char *build_prompt(char **env);

int	main(int ac, char **av, char **env)
{
	char *prompt;
	char *line;

	(void)ac;
	(void)av;
	prompt = NULL;
	line = NULL;
	welcome();
	for (int i = 0; i < 4; i++)
	{
		prompt = build_prompt(env);
		if (!prompt)
			exit(EXIT_FAILURE);
		line = readline(prompt);
		printf("\n%s\n", line);
		free(line);
	}

	return (0);
}