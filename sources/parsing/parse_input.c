#include "debug.h"
#include "lexing.h"
#include "parsing.h"
#include "token_formatting.h"

t_input	*parse_input(char *line, char *prompt)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return ((void *)0);
	init_input(input, line, prompt);
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		return ((void *)0);
	if (!tokenize_input(input, line))
		return ((void *)0);
	print_input(input, "TOKENIZED");
	// format_tokens(input);
	// print_input(input, "FORMATTED TOKENS");
	// format_input(input);
	// print_input(input, "FORMATTED INPUT");

	return (input);
}
