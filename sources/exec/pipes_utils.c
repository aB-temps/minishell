#include "exec.h"
#include "input.h"

void	close_all(t_fd *fd)
{
	if (fd->fd1[0] != -1)
		close(fd->fd1[0]);
	if (fd->fd1[1] != -1)
		close(fd->fd1[1]);
	if (fd->fd2[0] != -1)
		close(fd->fd2[0]);
	if (fd->fd2[1] != -1)
		close(fd->fd2[1]);
}

void	close_and_swap_pipes(t_fd *fd, int mod)
{
	close_all(fd);
	fd->fd1[0] = fd->fd2[0];
	fd->fd1[1] = fd->fd2[1];
}

int	create_pipe(t_fd *fd)
{
	if (pipe(fd->fd1) == -1)
		return (1);
	return (0);
}
