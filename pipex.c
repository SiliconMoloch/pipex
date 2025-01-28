/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:46:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/24 17:46:23 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		main(int argc, char **argv, char **env);
void	child_processing(char **argv, int pipe_fd[2], char **env);
void	child_bis_processing(char **argv, int pipe_fd[2], char **env);
void	execute(char *command, char **env);
char	*ft_getenv(const char *var, char **env);

int	main(int argc, char **argv, char **env)

{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;
	pid_t	pid_bis;

	if (argc != 5)
		escape(WRONG_ARGC, 0);
	if (!env[0])
		escape(NO_ENV, 0);
	if (pipe(pipe_fd) < 0)
		escape(strerror(errno), 0);
	pid = fork();
	if (pid < 0)
		close_fds(pipe_fd, 1);
	else if (!pid)
		child_processing(argv, pipe_fd, env);
	pid_bis = fork();
	if (pid_bis < 0)
		close_fds(pipe_fd, 1);
	else if (!pid_bis)
		child_bis_processing(argv, pipe_fd, env);
	close_fds(pipe_fd, 0);
	waitpid(pid, &status, 0);
	waitpid(pid_bis, &status, 0);
	return (WEXITSTATUS(status));
}

void	child_processing(char **argv, int pipe_fd[2], char **env)

{
	int	fd;

	fd = open_file(argv[1], 0, pipe_fd);
	if (dup2(fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		close(fd);
		close_fds(pipe_fd, 1);
	}
	close(fd);
	close_fds(pipe_fd, 0);
	execute(argv[2], env);
}

void	child_bis_processing(char **argv, int pipe_fd[2], char **env)

{
	int	fd;

	fd = open_file(argv[4], 1, pipe_fd);
	if (dup2(fd, STDOUT_FILENO) < 0 || dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		close(fd);
		close_fds(pipe_fd, 1);
		escape(strerror(errno), 0);
	}
	close(fd);
	close_fds(pipe_fd, 0);
	execute(argv[3], env);
}

void	execute(char *command, char **env)

{
	char	**cmd_args;
	char	**paths;
	char	*path_env;
	char	*whole_path;
	int		i;

	cmd_args = ft_split(command, ' ');
	paths = ft_split(ft_getenv("PATH", env), ':');
	if (!paths || !cmd_args)
		release_then_escape(0, strerror(errno), paths, cmd_args);
	i = 0;
	while (paths[i])
	{
		path_env = ft_strjoin(paths[i], "/");
		whole_path = ft_strjoin(path_env, cmd_args[0]);
		free(path_env);
		if (!whole_path)
			release_then_escape(0, strerror(errno), paths, cmd_args);
		if (!access(whole_path, F_OK | X_OK))
			execve(whole_path, cmd_args, env);
		free(whole_path);
		i++;
	}
	release_then_escape(2, ft_strjoin(ERR_MSG_II, command), paths, cmd_args);
}

char	*ft_getenv(const char *var, char **env)

{
	size_t	length;
	size_t	i;

	if (!var || !env)
		return (NULL);
	length = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, length) == 0 && env[i][length] == '=')
			return (env[i] + length + 1);
		i++;
	}
	return (NULL);
}
