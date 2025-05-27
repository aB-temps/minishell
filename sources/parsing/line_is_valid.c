# include "parsing.h"

bool	line_is_valid(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (true);
		i++;
	}
	return (false);
}
