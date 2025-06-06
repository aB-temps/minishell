#include "debug.h"
#include "parsing.h"

static void	tokenize_redir(t_input *input, size_t *i, char *line,
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
}

static void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (is_redir_or_pipe(line[*i]))
		tokenize_redir(input, i, line, line_len);
	input->token_qty++;
}

static void	tokenize_arg(t_input *input, size_t *i, char *line)
{
	char	*raw_content;
	int		token_type;
	size_t	j;

	j = *i;
	if (line[*i] == '\'')
		token_type = S_QUOTES;
	else if (line[*i] == '"')
		token_type = D_QUOTES;
	else
		token_type = ARG;
	// peaufiner is_valid_arg : reste peu de cas
	while (line[*i] && is_valid_arg_char(line[*i]))
		(*i)++;
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, raw_content);
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
		else if (is_valid_arg_char(line[i]))
			// peaufiner is_valid_arg : reste peu de cas
			tokenize_arg(input, &i, line);
		else
			i++;
	}
}
