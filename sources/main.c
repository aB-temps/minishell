#include "parsing.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	welcome();
	get_input(env);

	return (0);
}