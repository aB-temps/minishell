#include "libft.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

char	*build_prompt(char *username)
{
	char	*cwd;
	char	*prompt;

	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	prompt = ft_strjoin(FG_BLUE BOLD, username);
	if (!prompt)
		return (NULL);
	prompt = str_free_to_join(prompt, FG_GREEN " ");
	if (!prompt)
		return (NULL);
	prompt = str_free_to_join(prompt, cwd);
	if (!prompt)
		return (NULL);
	prompt = str_free_to_join(prompt, " ⚡> " R_ALL);
	if (!prompt)
		return (NULL);
	return (prompt);
}
