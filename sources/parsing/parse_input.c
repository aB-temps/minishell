#include "libft.h"
#include "parsing.h"

t_input	*parse_input(char *line)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return ((void *)0);
	init_input(input);
	input->v_tokens = create_vector(5, sizeof(t_token),
			clear_token(input->v_tokens));
	if (!input->v_tokens)
		return ((void *)0);
	// count_tokens();
	tokenize_input(input, line);
	// format_input(input);
	return (input);
}
