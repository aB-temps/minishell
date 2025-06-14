#include "token_formatting.h"

char	*str_replace(char *s, char *old, char *new)
{
	const size_t	old_len = ft_strlen(old);
	const size_t	total_len = ft_strlen(s) - (count_occurence(s, old)
				* old_len) + (count_occurence(s, old) * ft_strlen(new));
	char			*ns;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ns = ft_calloc(sizeof(char), total_len + 1);
	if (!ns)
		return ((void *)0);
	while (s[i])
	{
		if (!ft_strncmp(&s[i], old, old_len) && (is_whitespace(s[i + old_len])
				|| is_quote(s[i + old_len]) || s[i] == '$' || !s[i + old_len]))
		{
			i += old_len;
			j += ft_strlen(new);
			ft_strlcat(ns, new, j + 1);
		}
		else
			ns[j++] = s[i++];
	}
	ns[total_len] = '\0';
	return (ns);
}
