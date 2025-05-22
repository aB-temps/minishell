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

void	handle_single_quote(char *line, t_list **lexing_list, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	if (line[*i] == '\'')
	{
		start = *i;
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] == '\'')
		{
			content = ft_substr(line, start + 1, *i - start - 1); // pas protégé
			token = create_token(TOKEN_SINGLE_QUOTE, content);
			ft_lstadd_back(lexing_list, ft_lstnew(token));
			(*i)++;
		}
		else
		{
			content = ft_substr(line, start + 1, *i - start - 1); // pas protégé
			token = create_token(TOKEN_ERROR, content);
			ft_lstadd_back(lexing_list, ft_lstnew(token));
		}
	}
}

void	handle_double_quote(char *line, t_list **lexing_list, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	if (line[*i] == '\"')
	{
		start = *i;
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (line[*i] == '\"')
		{
			content = ft_substr(line, start + 1, *i - start - 1); // pas protégé
			token = create_token(TOKEN_DOUBLE_QUOTE, content);
			ft_lstadd_back(lexing_list, ft_lstnew(token));
			(*i)++;
		}
		else
		{
			content = ft_substr(line, start + 1, *i - start - 1); // pas protégé
			token = create_token(TOKEN_ERROR, content);
			ft_lstadd_back(lexing_list, ft_lstnew(token));
		}
	}
}

void	handle_word(char *line, t_list **lexing_list, size_t *i)
{
	size_t	start;
	char	*content;
	t_token	*token;

	if (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		start = *i;
		while (line[*i] && line[*i] != ' ' && line[*i] != '\''
			&& line[*i] != '\"' && line[*i] != '|' && line[*i] != '<'
			&& line[*i] != '>')
			(*i)++;
		content = ft_substr(line, start, *i - start); // pas protégé
		token = create_token(TOKEN_WORD, content);
		ft_lstadd_back(lexing_list, ft_lstnew(token));
	}
}

void	put_lex(char *line, t_list **lexing_list)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '\'')
			handle_single_quote(line, lexing_list, &i);
		else if (line[i] == '\"')
			handle_double_quote(line, lexing_list, &i);
		else if (line[i] == '|')
		{
			token = create_token(TOKEN_PIPE, ft_strdup("|"));
			ft_lstadd_back(lexing_list, ft_lstnew(token));
			i++;
		}
		else
			handle_word(line, lexing_list, &i);
	}
}

void	print_lexing(t_list *lexing_list)
{
	t_list	*current;
	t_token	*token;

	current = lexing_list;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		ft_printf("Token type: %d, Content: \"%s\"\n", token->type, token->content); // utiliser vrai printf
		current = current->next;
	}
}

int	lexing(char *line)
{
	t_list	*lexing_list;

	if (!line)
		return (1);
	lexing_list = NULL;
	put_lex(line, &lexing_list);
	print_lexing(lexing_list);
	return (0);
}
