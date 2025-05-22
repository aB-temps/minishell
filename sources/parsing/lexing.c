#include "lexing.h"

t_token	*create_token(int type, char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->content = content;
	return (new_token);
}

t_token	*handle_single_quote(char *line, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	token = NULL;
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
	{
		content = ft_substr(line, start + 1, *i - start - 1);
		token = create_token(TOKEN_SINGLE_QUOTE, content);
		(*i)++;
	}
	else
	{
		content = ft_substr(line, start + 1, *i - start - 1);
		token = create_token(TOKEN_ERROR, content);
	}
	return (token);
}

t_token	*handle_double_quote(char *line, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	token = NULL;
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (line[*i] == '\"')
	{
		content = ft_substr(line, start + 1, *i - start - 1);
		token = create_token(TOKEN_DOUBLE_QUOTE, content);
		(*i)++;
	}
	else
	{
		content = ft_substr(line, start + 1, *i - start - 1);
		token = create_token(TOKEN_ERROR, content);
	}
	return (token);
}

t_token	*handle_less_than(char *line, size_t *i)
{
	t_token	*token;

	token = NULL;
	if (line[*(i) + 1] == '<')
	{
		token = create_token(TOKEN_HEREDOC, ft_strdup("<<"));
		(*i)++;
	}
	else
		token = create_token(TOKEN_REDIRECT_IN, ft_strdup("<"));
	(*i)++;
	return (token);
}

t_token	*handle_greater_than(char *line, size_t *i)
{
	t_token	*token;

	token = NULL;
	if (line[*i + 1] == '>')
	{
		token = create_token(TOKEN_APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else
		token = create_token(TOKEN_REDIRECT_OUT, ft_strdup(">"));
	(*i)++;
	return (token);
}

t_token	*handle_word(char *line, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	token = NULL;
	if (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		start = *i;
		while (line[*i] && line[*i] != ' ' && line[*i] != '\''
			&& line[*i] != '\"' && line[*i] != '|' && line[*i] != '<'
			&& line[*i] != '>')
			(*i)++;
		content = ft_substr(line, start, *i - start);
		token = create_token(TOKEN_WORD, content);
	}
	return (token);
}

int	put_lex(char *line, t_list **lexing_lst)
{
	size_t	i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (!line[i])
			break ;
		if (line[i] == '\'')
			token = handle_single_quote(line, &i);
		else if (line[i] == '>')
			token = handle_greater_than(line, &i);
		else if (line[i] == '\"')
			token = handle_double_quote(line, &i);
		else if (line[i] == '<')
			token = handle_less_than(line, &i);
		else if (line[i] == '|')
		{
			token = create_token(TOKEN_PIPE, ft_strdup("|"));
			i++;
		}
		else if (line[i] == ' ')
		{
			token = create_token(TOKEN_WHITESPACE, ft_strdup(" "));
			while (line[i] == ' ')
				i++;
		}
		else
			token = handle_word(line, &i);
		if (token == NULL)												//DEBUG
		{
			printf("[DEBUG]: Error un lexing.c\n");
			printf("[DEBUG]: token = NULL\n");
			return (1);
		}
		else if (token->content == NULL)
		{
			printf("[DEBUG]: Error un lexing.c\n");
			printf("[DEBUG]: token->content = %s\n", token->content);
			return (1);
		}																//DEBUG
		
		ft_lstadd_back(lexing_lst, ft_lstnew(token));
	}
	return (0);
}

void	print_lexing(t_list *lexing_lst)
{
	t_list	*current;
	t_token	*token;

	current = lexing_lst;
	if (current == NULL)
		printf("No token\n");
	while (current != NULL)
	{
		token = (t_token *)current->content;
		printf("Token type: %d, Content: \"%s\"\n", token->type,
			token->content);
		current = current->next;
	}
}

int	lexing(char *line, t_list **lexing_lst)
{
	if (!line)
		return (0);
	if (put_lex(line, lexing_lst) == 1)
		return (1);
	print_lexing(*lexing_lst);
	return (0);
}
