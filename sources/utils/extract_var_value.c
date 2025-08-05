#include "token_formatting.h"

t_env_var	last_exit_status_to_var(t_input *input)
{
	t_env_var	var;

	var.value = (void *)0;
	var.key = ft_strdup("$?");
	if (!var.key)
		return (var);
	var.value = ft_itoa(input->last_exit_status);
	return (var);
}

t_env_var	string_to_var(char *s, t_input *input)
{
	t_env_var var;

	var.value = (void *)0;
	var.key = extract_var_key(s);
	if (!var.key)
		return (var);
	var.value = get_env_value(var.key + 1, input);
	return (var);
}