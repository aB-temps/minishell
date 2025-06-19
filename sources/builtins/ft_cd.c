#include "builtins.h"

void	ft_cd(char *path)
{
	if (chdir(path) == -1)
		return ; // ????? WHAT TO DO
}