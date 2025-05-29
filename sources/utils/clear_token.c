#include "input.h"

void	clear_token(t_vector *tokens)
{
	int i;

	i = 0;
	while (i < tokens->occupied_bytes)
	{
		free(((t_token *)tokens->array + i)->raw_content);
		if (((t_token *)tokens->array + i)->type == COMMAND)
			free_tab_return_null(((char **)((t_token *)tokens->array
						+ i)->formatted_content));
		else
			free(((t_token *)tokens->array + i)->formatted_content);
		i += tokens->datatype_size;
	}
}