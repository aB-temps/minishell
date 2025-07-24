#include "input.h"

void	clear_var_vector(t_vector *v_var_array)
{
	t_env_var	*var_array;
	size_t		i;

	var_array = (t_env_var *)v_var_array->array;
	i = 0;
	while (i < v_var_array->nb_elements)
	{
		if (var_array[i].key)
		{
			free(var_array[i].key);
			var_array[i].key = (void *)0;
		}
		if (var_array[i].value)
		{
			free(var_array[i].value);
			var_array[i].value = (void *)0;
		}
		i++;
	}
}