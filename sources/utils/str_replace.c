#include "checking.h"
#include "libft.h"
#include <stdio.h>

size_t	count_occurence(char *s, char *to_find)
{
	size_t	count;
	char	*cursor;

	count = 0;
	cursor = s;
	while (to_find && cursor)
	{
		cursor = ft_strnstr(s, to_find, ft_strlen(s));
		if (cursor)
			count++;
		s = cursor + ft_strlen(to_find);
	}
	return (count);
}

char	*str_replace(char *s, char *old, char *new)
{
	const size_t	new_total_len = ft_strlen(s) - (count_occurence(s, old)
				* ft_strlen(old)) + (count_occurence(s, old) * ft_strlen(new));
	char			*ns;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ns = ft_calloc(sizeof(char), new_total_len + 1);
	if (!ns || !old || !new || !s)
		return ((void *)0);
	while (s[i])
	{
		if (!ft_strncmp(&s[i], old, ft_strlen(old)) && (is_whitespace(s[i
					+ ft_strlen(old)]) || !s[i + ft_strlen(old)]))
		{
			i += ft_strlen(old);
			j += ft_strlen(new);
			ft_strlcat(ns, new, j + 1);
		}
		else
			ns[j++] = s[i++];
	}
	ns[new_total_len] = '\0';
	return (ns);
}
