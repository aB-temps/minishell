#include "exec.h"
#include "input.h"

void	error_occured(t_fd *fd, char *error_msg)
{
	if (error_msg != NULL)
		perror(error_msg);
	close_all(fd);
	exit(1);
}

void	first_cmd(t_fd *fd, char *file_name)
{
	int	infile;

	if (!file_name)
	{
		if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
			error_occured(fd, "dup2");
		close_all(fd);
		return ;
	}
	if (ft_strncmp(file_name, "/dev/stdin", 10) == 0)
		infile = STDIN_FILENO;
	else
	{
		infile = open(file_name, O_RDONLY);
		if (infile == -1)
			error_occured(fd, file_name);
	}
	if (infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			close(infile);
			error_occured(fd, "dup2");
		}
		close(infile);
	}
	if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(fd, "dup2");
	close_all(fd);
}

void	middle_cmd(t_fd *fd)
{
	if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(fd, "dup2");
	if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
		error_occured(fd, "dup2");
	close_all(fd);
}

void	last_cmd(t_fd *fd, char *file_name)
{
	int	outfile;

	if (!file_name)
	{
		if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
			error_occured(fd, "dup2");
		close_all(fd);
		return ;
	}
	if (ft_strncmp(file_name, "/dev/stdout", 11) == 0)
		outfile = STDOUT_FILENO;
	else
	{
		outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			error_occured(fd, file_name);
	}
	if (outfile != STDOUT_FILENO)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			close(outfile);
			error_occured(fd, "dup2");
		}
		close(outfile);
	}
	if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
		error_occured(fd, "dup2");
	close_all(fd);
}

void	init_fd(t_fd *fd)
{
	fd->fd1[0] = -1;
	fd->fd1[1] = -1;
	fd->fd2[0] = -1;
	fd->fd2[1] = -1;
}

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

void	close_and_swap_pipes(t_fd *fd)
{
	close_all(fd);
	fd->fd1[0] = fd->fd2[0];
	fd->fd1[1] = fd->fd2[1];
}

void	prepare_pipe(t_exec *exec, t_fd *fd, int i)
{
	if (i == 0)
		first_cmd(fd, exec->infile);
	else if (i == exec->cmd_count - 1)
		last_cmd(fd, exec->outfile);
	else
		middle_cmd(fd);
}
