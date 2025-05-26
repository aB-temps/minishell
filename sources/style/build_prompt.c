#include "libft.h"
#include <linux/limits.h>
#include <unistd.h>

static char	*get_hostname(char *env_session)
{
	int	i;

	i = 0;
	while (env_session[i] != '.')
		i++;
	env_session[i] = '\0';
	env_session = &env_session[ft_strlen("local/")];
	return (env_session);
}

void	build_prompt(char **prompt)
{
	const char	*username = getenv("USER");
	const char	*hostname = get_hostname(getenv("SESSION_MANAGER"));
	char		*cwd;
	size_t		plen;

	cwd = (void *)0;
	cwd = getcwd(cwd, PATH_MAX);
	if (!cwd)
		return ;
	plen = ft_strlen(username) + ft_strlen(hostname) + ft_strlen(cwd) + 4;
	*prompt = calloc(plen, sizeof(char));
	ft_strlcat(*prompt, username, plen);
	ft_strlcat(*prompt, "@", plen);
	ft_strlcat(*prompt, hostname, plen);
	ft_strlcat(*prompt, "	", plen);
	ft_strlcat(*prompt, cwd, plen);
	ft_strlcat(*prompt, "	\0", plen);
	free(cwd);
}
