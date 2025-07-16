#include "debug.h"
#include "lexing.h"
#include "parsing.h"
#include "token_formatting.h"

void	read_heredoc(t_token *token, t_input *input)
{
	char	*heredoc_value;
	char	*line;

	(void)input;
	heredoc_value = ft_strdup("");
	line = (void *)0;
	while (1)
	{
		line = readline("heredoc>");
		if (!ft_strncmp(line, (char *)token->formatted_content,
				ft_strlen((char *)token->formatted_content)))
			break ;
		heredoc_value = str_free_to_join(heredoc_value, "\n");
		heredoc_value = str_free_to_join(heredoc_value, line);
	}
	printf("heredoc ===> %s\n", heredoc_value);
}

void	handle_heredoc(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type == HEREDOC)
		{
			read_heredoc(&array[i], input);
		}
		i++;
	}
}

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
	print_input(input, "FORMATTED INPUT");
	handle_heredoc(input);
	return (input);
}
