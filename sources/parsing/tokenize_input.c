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
	input->token_qty++;
}

static void	tokenize_arg(t_input *input, size_t *i, int token_type, char *line)
{
	char	*raw_content;
	size_t	j;

	j = *i;
	while (line[*i] && is_valid_arg_char(line[*i]))
	{
		(*i)++;
	}
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, raw_content);
	input->token_qty++;
}

static void	tokenize_operator(t_input *input, size_t *i, char *line,
		size_t line_len)
{
	if (is_redir_or_pipe(line[*i]))
		tokenize_redir(input, i, line, line_len);
	else if (is_var_or_assign(line[*i]))
		tokenize_arg(input, i, ENV_VAR, line);
}

static void	*tokenize_quote_arg(t_input *input, size_t *i, int token_type,
		char *line)
{
	ssize_t	j;
	char	*content;

	j = *i + 1;
	if (line[*i] == '\'')
		token_type = S_QUOTES;
	else
		token_type = D_QUOTES;
	while (line[++(*i)])
	{
		if ((token_type == S_QUOTES && line[*i] == '\'')
				|| (token_type == D_QUOTES && line[*i] == '"'))
			break ;
	}
	if (!line[*i])
		return ((void *)0);
	content = ft_strndup(&line[j], (*i)++ - j);
	if (!content)
		exit_minishell(input, EXIT_FAILURE);
	create_token(input, token_type, content);
	input->token_qty++;
	return (input);
}

void	*tokenize_input(t_input *input, char *line)
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
			tokenize_arg(input, &i, ARG, line);
		else if (is_quote(line[i]))
		{
			if (!tokenize_quote_arg(input, &i, ARG, line))
				return ((void *)0);
		}
		else
			i++;
	}
	return (input);
}
