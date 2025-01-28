/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:02:20 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/28 16:10:20 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	release_memory(char **array);
void	escape(char *error_message, int x);
void	release_then_escape(int x, char *err_msg, char **paths, char **cmd_arg);
int		open_file(char *path_to_file, int parent_process, int pipe_fd[2]);
void	close_fds(int pipe_fd[2], int flag);

void	release_memory(char **array)

{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	escape(char *error_message, int x)

{
	write(2, "pipex: ", 8);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	if (x)
		free(error_message);
	exit(EXIT_FAILURE);
}

void	release_then_escape(int x, char *err_msg, char **paths, char **cmd_arg)

{
	if (err_msg)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		if (x)
			free(err_msg);
		if (paths)
			release_memory(paths);
		if (cmd_arg)
			release_memory(cmd_arg);
		if (x == 2)
			exit(127);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		if (paths)
			release_memory(paths);
		if (cmd_arg)
			release_memory(cmd_arg);
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *path_to_file, int child_bis, int pipe_fd[2])

{
	int	fd;

	if (!child_bis)
		fd = open(path_to_file, O_RDONLY, 0644);
	else
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		close_fds(pipe_fd, 0);
		escape(ft_strjoin(path_to_file, ERR_MSG), 1);
	}
	return (fd);
}

void	close_fds(int pipe_fd[2], int flag)

{
	char	*temp;

	if (flag)
		temp = strerror(errno);
	if (close(pipe_fd[0]) < 0)
		escape(strerror(errno), 0);
	if (close(pipe_fd[1]) < 0)
		escape(strerror(errno), 0);
	if (flag)
		escape(strerror(errno), 0);
}
