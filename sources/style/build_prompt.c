# include "libft.h"
# include <linux/limits.h>
# include <unistd.h>

void	build_prompt(char *prompt[_SC_LOGIN_NAME_MAX + PATH_MAX], char **env)
{
	const char *username = getenv("USER");
	char *cwd;
	size_t prompt_max;
	(void)env;
	cwd = (void *)0;
	prompt_max = _SC_LOGIN_NAME_MAX + PATH_MAX + 1;
	cwd = getcwd(cwd, PATH_MAX);

	*prompt = (char *)username;
	ft_strlcat(*prompt, "    ", prompt_max);
	ft_strlcat(*prompt, cwd, prompt_max);
}