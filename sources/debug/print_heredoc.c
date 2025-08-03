#include "debug.h"

void	print_token_heredoc(t_token token)
{
	// char	*line;

	printf("fds[%s%i%s|%s%i%s]\n'", BOLD, ((int *)token.formatted_content)[0],
		R_ALL, BOLD, ((int *)token.formatted_content)[1], R_ALL);
	// line = get_next_line(((int *)token.formatted_content)[1]);
	// while (line)
	// {
	// 	printf("%s%s%s", DIM, line, R_ALL);
	// 	free(line);
	// 	line = get_next_line(((int *)token.formatted_content)[1]);
	// }
	// if (line)
	// 	free(line);
	// printf("'\n");
	// close(((int *)token.formatted_content)[1]);
}
