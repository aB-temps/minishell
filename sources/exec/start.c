#include "exec.h"

int	start_exec(t_token *token, char **env)
{
	t_data	data;
	t_fd	fd;
	int		return_value;

	data.env = env;
	return_value = ft_pipex(&data, &fd);
	free_all(&data);
	close_all(&fd);
	return (return_value);
}
