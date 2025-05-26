#include "env.h"

void	build_prompt(char *prompt, char **env)
{
	const char *username = get_line_in_env(env, "USER=");
	char *cwd;

	cwd = NULL;
	getcwd(cwd, PATH_MAX);
	prompt = (char *)username;
	ft_printf("%s\n", prompt);
	ft_strlcat(prompt, cwd, ft_strlen(cwd));
	ft_printf("%s\n", prompt);
}