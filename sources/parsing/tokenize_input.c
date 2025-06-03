#include "debug.h"
#include "parsing.h"

void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (line[*i] == '|')
		create_token(input, PIPE, "|");
	else if (line[*i] == '>')
	{
		if (*i < line_len - 1 && line[*i + 1] == '>')
		{
			create_token(input, APPEND, ">>");
			(*i)++;
		}
		else
			create_token(input, REDIR_OUT, ">");
	}
	else if (line[*i] == '<')
		create_token(input, REDIR_IN, "<");
	(*i)++;
	input->token_qty++;
}

void	tokenize_arg(t_input *input, size_t *i, char *line)
{
	char	*raw_content;
	size_t	j;

	j = *i;
	while (line[*i] && is_valid_arg_char(line[*i])) // peaufiner is_valid_arg
		(*i)++;
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, ARG, raw_content);
	input->token_qty++;
}

void	tokenize_input(t_input *input, char *line)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (is_operator(line[i]))
			tokenize_operator(input, &i, line, line_len);
		else if (is_valid_arg_char(line[i])) // peaufiner is_valid_arg
			tokenize_arg(input, &i, line);
		else
			i++;
	}
	// print_input(input);
}
