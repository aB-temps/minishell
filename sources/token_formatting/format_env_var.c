/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 22:29:42 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static t_env_var	last_exit_status_to_var(t_input *input)
{
	t_env_var	var;

	var.key = ft_strdup("$?");
	if (!var.key)
		exit_minishell(input, EXIT_FAILURE);
	var.value = ft_itoa(input->last_exit_status);
	if (!var.value)
	{
		free(var.key);
		exit_minishell(input, EXIT_FAILURE);
	}
	return (var);
}

static t_env_var	string_to_var(char *s, t_input *input)
{
	t_env_var	var;

	var.key = extract_var_key(s);
	if (!var.key)
		exit_minishell(input, EXIT_FAILURE);
	var.value = get_env_value(var.key + 1, input);
	if (!var.value)
	{
		free(var.key);
		exit_minishell(input, EXIT_FAILURE);
	}
	return (var);
}

static t_vector	*parse_env_var(char *s, t_input *input)
{
	t_vector	*var_array;
	t_env_var	var;
	size_t		i;

	i = 0;
	var_array = create_vector(1, sizeof(t_env_var), clear_var_vector);
	if (!var_array)
		exit_minishell(input, EXIT_FAILURE);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1])
				|| s[i + 1] == '?'))
		{
			if (s[i + 1] == '?')
				var = last_exit_status_to_var(input);
			else
				var = string_to_var(&s[i], input);
			if (!add_element(var_array, &var))
				exit_minishell(input, EXIT_FAILURE);
			i += ft_strlen(var.key);
		}
		else
			i++;
	}
	return (var_array);
}

static char	*replace_env_var(char *s, t_vector *v_var_array, t_input *input,
		size_t new_len)
{
	const t_env_var	*var_array = (t_env_var *)v_var_array->array;
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
	ns = replace_env_var(s, var_array, input, exp_var_strlen(s, var_array));
	clear_vector(&var_array);
	if (!ns)
		exit_minishell(input, EXIT_FAILURE);
	return (ns);
}
