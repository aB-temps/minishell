#include "parsing.h"

t_token	dup_token(t_token token)
{
	t_token	new_token;

	init_token(&new_token);
	new_token.type = token.type;
	new_token.raw_content = ft_strdup(token.raw_content);
	if (!new_token.raw_content)
	{
		new_token.type = -1;
		return (new_token);
	}
	if (token.type == COMMAND)
		new_token.formatted_content = tabdup(token.formatted_content);
	else
		new_token.formatted_content = ft_strdup(token.formatted_content);
	if (!new_token.formatted_content)
		new_token.type = -1;
	return (new_token);
}
