#include "builtins.h"

void	ft_pwd(void)
{
	char *cwd;

	cwd = (void *)0;
	cwd = getcwd(cwd, PATH_MAX);
	if (!cwd)
		return ; // WHAT TO DO
	printf("%s\n", cwd);
	free(cwd);
}