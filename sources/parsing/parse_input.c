#include "debug.h"
#include "heredoc.h"

void	*parse_input(t_input *input)
{
	input->v_tokens = create_vector(4, sizeof(t_token), clear_token);
	if (!input->v_tokens)
		exit_minishell(input, EXIT_FAILURE);
	tokenize_input(input, input->line);
	print_input(input, "TOKENIZED");
	if (!check_syntax_error(input))
	{
		ft_putstr_fd(BOLD FG_RED"minishell: syntax error\n"R_ALL, STDERR_FILENO);
		return ((void *)0);
	}
	format_tokens(input);
	print_input(input, "FORMATTED TOKENS");
	format_input(input, (t_token *)input->v_tokens->array);
	handle_heredoc(input);
	print_input(input, "FORMATTED INPUT");
	return (input);
}
