#include "token_formatting.h"

static char	*get_var_key(char *s)
{
	char	*raw_var_name;
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start] && s[start] != '$')
		start++;
	end = start + 1;
	while (s[end] && s[end] != '$' && ft_isalnum(s[end]))
		end++;
	raw_var_name = ft_strndup(s + start, end - start);
	if (!raw_var_name)
		return ((void *)0);
	return (raw_var_name);
}

void	clear_var_array(t_vector *v_var_array)
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

t_vector	*parse_env_var(char *s, t_input *input)
{
	t_vector	*var_array;
	t_env_var	var;
	size_t		i;

	i = 0;
	var_array = create_vector(1, sizeof(t_env_var), clear_var_array);
	if (!var_array)
		exit_minishell(input, EXIT_FAILURE);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i
				+ 1] == '?'))
		{
			if (s[i + 1] == '?')
			{
				var.key = ft_strdup("$?");
				if (!var.key)
					exit_minishell(input, EXIT_FAILURE);
				var.value = ft_itoa(input->last_exit_status);
				if (!var.value)
					exit_minishell(input, EXIT_FAILURE);
			}
			else
			{
				var.key = get_var_key(&s[i]);
				if (!var.key)
					exit_minishell(input, EXIT_FAILURE);
				var.value = get_env_var(var.key + 1, input);
				if (!var.value)
					exit_minishell(input, EXIT_FAILURE);
			}
			printf("var.key => %s\n", var.key);
			printf("var.value => %s\n", var.value);
			if (!add_element(var_array, &var))
				exit_minishell(input, EXIT_FAILURE);
			i += ft_strlen(var.key);
		}
		else
			i++;
	}
	return (var_array);
}

char	*substitute_env_var(char *s, t_input *input)
{
	t_vector	*var_array;

	// char		*ns;
	// ns = (void *)0;
	var_array = parse_env_var(s, input);
	if (!var_array)
		exit_minishell(input, EXIT_FAILURE);
	// ns = replace_env_var(var_array, input);
	clear_vector(&var_array);
	// if (!ns)
	// 	exit_minishell(input, EXIT_FAILURE);
	return (NULL);
}

void	format_env_var(t_input *input, t_token *array, ssize_t *i)
{
	array[*i].formatted_content = substitute_env_var(array[*i].raw_content,
			input);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = ENV_VAR;
	(*i)++;
}
