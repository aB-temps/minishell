#include "builtins.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t	i;

	i = 0;
	if (length == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < length - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	bool			n_param;
	size_t			i;

	i = 0;
	while (i < args_qty)
	{
		if (args[i][0] == '-' && count_occurences)
		{
			if (ft_strncmp(args[i], "-n", ft_strlen("-n")))
				n_param = true;
		}
		else
		{
			printf("%s", args[i]);
			if (i < args_qty - 1)
				printf(" ");
		}
		i++;
	}
	if (!n_param)
		printf("\n");
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	ft_echo(av + 1);
	return (0);
}