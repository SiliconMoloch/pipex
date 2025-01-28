/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:02:20 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/27 14:46:38 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	release_memory(char **array);
void	escape(char *error_message, int x);
void	release_then_escape(int x, char *err_msg, char **paths, char **cmd_arg);
void	here_doc(char *limiter, int pipe_fd[2]);
int		open_file(char *path_to_file, int parent_process, int pipe_fd[2]);

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
		if (x)
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

int	open_file(char *path_to_file, int parent_process, int pipe_fd[2])

{
	int	fd;

	if (!parent_process)
	{
		fd = open(path_to_file, O_RDONLY, 0644);
		if (fd < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			escape(ft_strjoin(path_to_file, ERR_MSG), 1);
		}
	}
	else
	{
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			escape(ft_strjoin(path_to_file, ERR_MSG), 1);
		}
	}
	return (fd);
}

void	here_doc(char *limiter, int pipe_fd[2])

{
	char	*line;
	size_t	limiter_size;
	int		i;

	limiter_size = ft_strlen(limiter);
	i = 1;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO, limiter, &i);
		if (!line || !ft_strncmp(limiter, line, limiter_size))
		{
			free(line);
			break ;
		}
		if (write(pipe_fd[1], line, ft_strlen(line)) < 0)
		{
			free(line);
			escape(strerror(errno), 0);
		}
		free(line);
	}
	close(pipe_fd[1]);
}
