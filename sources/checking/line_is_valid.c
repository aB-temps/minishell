# include "parsing.h"

bool	is_valid_line(char *line)
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
