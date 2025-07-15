#include "debug.h"
#include "lexing.h"
#include "parsing.h"
#include "token_formatting.h"

t_input	*parse_input(char *line, char *prompt, int exit_status)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return ((void *)0);
	init_input(input, line, prompt, exit_status);
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		return ((void *)0);
	if (!tokenize_input(input, line))
		return ((void *)0);
	// print_input(input, "TOKENIZED");
	format_tokens(input);
	// print_input(input, "FORMATTED TOKENS");
	if (!check_syntax_error(input))
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		clear_vector(input->v_tokens);
		free(input);
		return ((void *)0);
	}
	format_input(input);
	// print_input(input, "FORMATTED INPUT");
	return (input);
}
