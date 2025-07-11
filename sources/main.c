#include "parsing.h"
#include "style.h"
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	welcome();
	get_input(env);
	return (0);
}
