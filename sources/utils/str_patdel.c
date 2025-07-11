#include "token_formatting.h"

char	*str_patdel(char *s, char *pat)
{
	const size_t new_total_len = ft_strlen(s) - (countocc(s, pat)
			* ft_strlen(pat));
	char *ns;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (new_total_len == ft_strlen(s))
		return (s);
	ns = ft_calloc(sizeof(char), new_total_len + 1);
	if (!ns)
		return ((void *)0);
	while (i < new_total_len)
	{
		while (!ft_strncmp(&s[j], pat, ft_strlen(pat)))
			j += ft_strlen(pat);
		ns[i++] = s[j++];
	}
	ns[new_total_len] = '\0';
	return (ns);
}