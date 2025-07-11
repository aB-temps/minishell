#include "utils.h"

char	**ft_tabdup(char **tab)
{
	char	**new_tab;
	size_t	i;
	size_t	j;

	i = 0;
	new_tab = ft_calloc(ft_tablen(tab) + 1, sizeof(char *));
	if (!new_tab)
		return ((void *)0);
	while (tab[i])
	{
		j = 0;
		new_tab[i] = ft_calloc(ft_strlen(tab[i]) + 1, sizeof(char));
		if (!new_tab[i])
			return (free_tab_return_null(new_tab));
		while (j < ft_strlen(tab[i]))
		{
			new_tab[i][j] = tab[i][j];
			j++;
		}
		new_tab[i][j] = '\0';
		i++;
	}
	new_tab[i] = (void*)0;
	return (new_tab);
}
