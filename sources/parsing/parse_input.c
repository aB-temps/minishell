#include "debug.h"
#include "lexing.h"
#include "parsing.h"
#include "token_formatting.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		exit_minishell(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	print_input(input, "TOKENIZED");
	format_tokens(input);
	print_input(input, "FORMATTED TOKENS");
	if (!check_syntax_error(input))
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		return ((void *)0);
	}
	format_input(input);
	handle_heredoc(input);
	print_input(input, "FORMATTED INPUT + HEREDOC");
	return (input);
}
