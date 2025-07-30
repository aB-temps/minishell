#include "input.h"

bool	is_empty_var_token(t_token *array, ssize_t i)
{
	if (!(array[i].type == ENV_VAR && !ft_strlen(array[i].formatted_content)))
		return (true);
	else
		return (false);
}