#include "token_formatting.h"

char	*str_replace(char *s, char *old, char *new)
{
	const size_t	olen = ft_strlen(old);
	const size_t	ttlen = ft_strlen(s) - (countocc(s, old) * olen)
			+ (countocc(s, old) * ft_strlen(new));
	char			*ns;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ns = ft_calloc(sizeof(char), ttlen + 1);
	if (!ns)
		return ((void *)0);
	while (s[i])
	{
		if (!ft_strncmp(&s[i], old, olen) && (is_whitespace(s[i + olen])
				|| is_quote(s[i + olen]) || s[i] == '$' || !s[i + olen]))
		{
			i += olen;
			j += ft_strlen(new);
			ft_strlcat(ns, new, j + 1);
		}
		else
			ns[j++] = s[i++];
	}
	ns[ttlen] = '\0';
	return (ns);
}
