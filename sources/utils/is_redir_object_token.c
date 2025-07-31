#include "input.h"

bool	is_redir_object_token(t_token *array, ssize_t i)
{
	if (array[i].type < COMMAND)
		return (false);
	else
		return (true);
}
