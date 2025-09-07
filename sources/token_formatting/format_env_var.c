/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/07 14:37:05 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static void	*clean_env_var_parsing(t_vector *var_array, t_env_var *var)
{
	clear_var(var);
	clear_vector(&var_array);
	return ((void *)0);
}

static char	*replace_env_var(char *s, t_vector *v_var_array, size_t new_len)
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
		return ((void *)0);
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

static t_vector	*parse_env_var(char *s, t_input *input)
{
	t_vector	*var_array;
	t_env_var	var;
	size_t		i;

	i = 0;
	var_array = create_vector(1, sizeof(t_env_var), clear_var_vector);
	if (!var_array)
		return ((void *)0);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '?'
				|| s[i + 1] == '_'))
		{
			if (s[i + 1] == '?')
				var = last_exit_status_to_var(input);
			else
				var = string_to_var(&s[i], input);
			if (!var.value || !add_element(var_array, &var))
				return (clean_env_var_parsing(var_array, &var));
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
	char		*ns;

	ns = (void *)0;
	var_array = parse_env_var(s, input);
	if (!var_array)
		exit_parsing(input, EXIT_FAILURE);
	ns = replace_env_var(s, var_array, exp_var_strlen(s, var_array));
	clear_vector(&var_array);
	if (!ns)
		exit_parsing(input, EXIT_FAILURE);
	return (ns);
}
