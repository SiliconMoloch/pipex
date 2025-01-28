/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:50:47 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/27 15:18:03 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int		main(int argc, char **argv, char **env);
int		here_doc_case(int ac, char **av, int *o_fd, int p_fd[2]);
int		no_here_doc_case(int ac, char **av, t_fds *fds, int p_fd[2]);
void	handle_pipes(char *command, char **env);

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	int		i;
	t_fds	fds;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		escape(WRONG_ARGC, 0);
	if (!env[0])
		escape(NO_ENV, 0);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i = here_doc_case(argc, argv, &(fds.o_fd), pipe_fd);
	else
		i = no_here_doc_case(argc, argv, &(fds), pipe_fd);
	while (i < argc - 2)
	{
		handle_pipes(argv[i], env);
		i++;
	}
	if (dup2(fds.o_fd, STDOUT_FILENO) < 0)
		escape(strerror(errno), 0);
	close(fds.o_fd);
	execute(argv[argc - 2], env);
	return (EXIT_SUCCESS);
}

int	here_doc_case(int argc, char **argv, int *out_fd, int pipe_fd[2])
{
	if (pipe(pipe_fd) < 0)
		escape(strerror(errno), 0);
	here_doc(argv[2], pipe_fd);
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		escape(strerror(errno), 0);
	if (close(pipe_fd[0]))
		escape(strerror(errno), 0);
	*out_fd = open_file(argv[argc - 1], 1, pipe_fd);
	return (3);
}

int	no_here_doc_case(int ac, char **av, t_fds *fds, int p_fd[2])
{
	fds->i_fd = open_file(av[1], 0, p_fd);
	if (dup2(fds->i_fd, STDIN_FILENO) < 0)
	{
		close(fds->i_fd);
		close(p_fd[0]);
		close(p_fd[1]);
		escape(strerror(errno), 0);
	}
	fds->o_fd = open_file(av[ac - 1], 1, p_fd);
	return (2);
}

void	handle_pipes(char *command, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		escape(strerror(errno), 0);
	pid = fork();
	if (pid < 0)
		escape(strerror(errno), 0);
	if (!pid)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			escape(strerror(errno), 0);
		close(pipe_fd[1]);
		execute(command, env);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			escape(strerror(errno), 0);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}
