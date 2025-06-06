#include "debug.h"
#include "libft.h"
#include "parsing.h"

t_input	*parse_input(char *line)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return ((void *)0);
	init_input(input, line);
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		return ((void *)0);
	if (!tokenize_input(input, line))
		return ((void *)0);
	// print_input(input);
	format_input(input);
	print_input(input);
	return (input);
}
