#include "parsing.h"

void tokenize_operator(int i, char *s);

void tokenize_input(t_input *input, char *line)
{
	int i;

	i = 0;

	while (line[i])
	{
		if (is_operator(line[i]))
			tokenize_operator(i, line);
		
		i++;
	}
}
