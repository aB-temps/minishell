#include "checking.h"
#include <unistd.h>

static bool	are_quotes_paired(char *s)
{
	size_t	i;
	size_t	s_quotes;
	size_t	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (s[i])
	{
		if (d_quotes % 2 == 0 && s[i] == '\'')
			s_quotes++;
		else if (s_quotes % 2 == 0 && s[i] == '\"')
			d_quotes++;
		i++;
	}
	return (s_quotes % 2 == 0 && d_quotes % 2 == 0);
}

bool	is_valid_input(char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(line))
		return (false);
	if (!are_quotes_paired(line))
		return (false);
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (true);
		i++;
	}
	return (false);
}
