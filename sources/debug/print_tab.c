#include <debug.h>

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	printf("Formatted Content :\n");
	while (tab[i])
	{
		printf("[%i]: '%s'\n", i, tab[i]);
		i++;
	}
	printf("\n");
}
