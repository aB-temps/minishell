#include "libft.h"
#include "parsing.h"

t_input	*parse_input(char *line)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return ((void *)0);
	tokenize_input(input, line);
	// format_input(input);
	return (input);
}
