#include "token_formatting.h"

static void	clear_var_array(t_vector *v_var_array)
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

static char	*get_var_key(char *s)
{
	char	*var_key;
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start] && s[start] != '$')
		start++;
	end = start + 1;
	while (s[end] && s[end] != '$' && ft_isalnum(s[end]))
		end++;
	var_key = ft_strndup(s + start, end - start);
	if (!var_key)
		return ((void *)0);
	return (var_key);
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
			if (!add_element(var_array, &var))
				exit_minishell(input, EXIT_FAILURE);
			i += ft_strlen(var.key);
		}
		else
			i++;
	}
	return (var_array);
}

size_t	exp_var_strlen(char *s, t_vector *v_var_array)
{
	const t_env_var	*var_array = (t_env_var *)v_var_array->array;
	size_t			i;
	size_t			j;
	size_t			len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		if (j < v_var_array->nb_elements && !ft_strncmp(var_array[j].key, &s[i],
				ft_strlen(var_array[j].key)))
		{
			i += ft_strlen(var_array[j].key);
			len += ft_strlen(var_array[j++].value);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*replace_env_var(char *s, t_vector *v_var_array, t_input *input)
{
	const t_env_var	*var_array = (t_env_var *)v_var_array->array;
	const size_t	new_len = exp_var_strlen(s, v_var_array);
	char			*ns;
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	j = 0;
	k = 0;
	ns = ft_calloc(new_len + 1, sizeof(char));
	if (!ns)
		exit_minishell(input, EXIT_FAILURE);
	while (s[i])
	{
		if (j < v_var_array->nb_elements && !ft_strncmp(var_array[j].key, &s[i],
				ft_strlen(var_array[j].key)))
		{
			ft_strlcat(&ns[k], var_array[j].value, new_len + 1);
			k += ft_strlen(var_array[j].value);
			i += ft_strlen(var_array[j++].key);
		}
		else
			ns[k++] = s[i++];
	}
	ns[k] = '\0';
	return (ns);
}

char	*substitute_env_var(char *s, t_input *input)
{
	t_vector	*var_array;
	char		*ns;

	ns = (void *)0;
	var_array = parse_env_var(s, input);
	if (!var_array)
		exit_minishell(input, EXIT_FAILURE);
	ns = replace_env_var(s, var_array, input);
	clear_vector(&var_array);
	if (!ns)
		exit_minishell(input, EXIT_FAILURE);
	return (ns);
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
