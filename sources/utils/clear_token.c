#include "input.h"

void	clear_token(t_vector *tokens)
{
	const t_token *array = (t_token *)tokens->array;
	size_t i;

	i = 0;
	while (i < tokens->nb_elements)
	{
		free(array[i].raw_content);
		if (array[i].type == COMMAND)
			free_tab_return_null((char **)array[i].formatted_content);
		else
			free(array[i].formatted_content);
		i++;
	}
}