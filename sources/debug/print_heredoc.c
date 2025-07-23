#include "debug.h"

void	print_token_heredoc(t_token token)
{
	int		fd;
	char	*line;

	printf("fds[%s%i%s|%s%i%s]\n'", BOLD, ((int *)token.formatted_content)[0],
		R_ALL, BOLD, ((int *)token.formatted_content)[1], R_ALL);
	fd = dup(((int *)token.formatted_content)[1]);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s%s%s", DIM, line, R_ALL);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	printf("'\n");
	close(fd);
}
