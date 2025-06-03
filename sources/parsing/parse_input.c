#include "libft.h"
#include "parsing.h"
#include "debug.h"

t_input	*parse_input(char *line)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return ((void *)0);
	init_input(input);
	input->v_tokens = create_vector(4, sizeof(t_token),
			clear_token);
	if (!input->v_tokens)
		return ((void *)0);
	tokenize_input(input, line);
	// print_input(input);
	format_input(input);
	// print_input(input);
	return (input);
}
