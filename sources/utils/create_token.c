#include "parsing.h"

t_token	*create_token(t_token *token, int type, char *raw_content)
{
	token->type = type;
	token->raw_content = malloc(sizeof(char) * ft_strlen(raw_content) + 1);
	if (!token->raw_content)
		return ((void *)0);
	ft_strlcat(token->raw_content,raw_content, ft_strlen(raw_content)); 
	return (token);
}