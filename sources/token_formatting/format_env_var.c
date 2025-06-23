#include "token_formatting.h"

// UGLY TO REFACTOR

static char	*get_var_name(char *s, size_t *start)
{
	size_t	end;
	char	*var_name;

	end = 0;
	while (s[*start] && s[*start] != '$')
		(*start)++;
	end = *start + 1;
	while (s[end] && (s[end] != '$' && (ft_isalnum(s[end]) || s[end] == '-'
				|| s[end] == '_' || s[end] == '?')))
		(end)++;
	var_name = ft_strndup(s + *start, end - *start);
	return (var_name);
}

static char	*substitute_env_var_occurences(char *s, size_t *start,
		int exit_status)
{
	char	*ns;
	char	*var_name;
	char	*var_value;

	ns = (void *)0;        // UGLY TO REFACTOR
	var_value = (void *)0; // UGLY TO REFACTOR
	var_name = get_var_name(s, start);
	if (!var_name)
		return ((void *)0);
	if (ft_strlen(var_name) == 2 && var_name[1] == '?')
		var_value = ft_itoa(exit_status);
	else
		var_value = getenv(var_name + 1);
	if (!var_value)
		return ((void *)0);
	ns = str_replace(s, var_name, var_value);
	if (var_name[0] == '?')
		free(var_value);
	free(var_name);
	if (!ns)
		return ((void *)0);
	return (ns);
}

void	format_env_var(t_input *input, t_token *array, ssize_t *i)
{
	size_t	start;
	char	*content;
	char	*new_content;

	start = 0;
	content = substitute_env_var_occurences(array[*i].raw_content, &start,
			input->last_exit_status);
	while (content && ft_strchr(content, '$'))
	{
		start = 0;
		new_content = substitute_env_var_occurences(content, &start,
				input->last_exit_status);
		free(content);
		content = new_content;
	}
	array[*i].formatted_content = content;
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = ENV_VAR;
	(*i)++;
}
