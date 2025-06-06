#include "libft.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

static char	*get_hostname(char *env_session)
{
	int	i;

	i = 0;
	if (!env_session)
		return ((void *)0);
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
	if (!username || !hostname)
		return ; // protect
	cwd = getcwd(cwd, PATH_MAX);
	if (!cwd)
		return ; // protect
	plen = ft_strlen(username) + ft_strlen(hostname) + ft_strlen(cwd) + 5 + 59;
	*prompt = calloc(plen, sizeof(char));
	if (!(*prompt))
		return ; // protect
	ft_strlcat(*prompt, FG_CYAN BOLD, plen);
	ft_strlcat(*prompt, username, plen);
	ft_strlcat(*prompt, FG_MAGENTA "@" FG_CYAN, plen);
	ft_strlcat(*prompt, hostname, plen);
	ft_strlcat(*prompt, R_ALL "  👻  ", plen);
	ft_strlcat(*prompt, cwd, plen);
	ft_strlcat(*prompt, FG_MAGENTA "\n➤  " R_ALL "\0", plen);
	free(cwd);
}