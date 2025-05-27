#include "libft.h"
#include "parsing.h"

t_input	*parse_input(char *line)
{
	t_input *input;

	input = (void *)0;

	printf("line => %s\n", line);
	tokenize_input(input, line);

	// format_input(input);

	return (input);
}
