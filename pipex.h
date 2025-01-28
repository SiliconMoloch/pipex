/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:14:37 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/24 17:45:18 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define WRONG_ARGC "Wrong number of arguments"
# define NO_ENV "No environment variable"
# define ERR_MSG ": No such file or directory"
# define ERR_MSG_II "pipex: command not found: "

int		main(int argc, char **argv, char **env);
void	child_processing(char **argv, int pipe_fd[2], char **env);
void	child_bis_processing(char **argv, int pipe_fd[2], char **env);
void	execute(char *command, char **env);
char	*ft_getenv(const char *var, char **env);

int		ft_str_is_space(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);

void	release_memory(char **array);
void	escape(char *error_message, int x);
void	release_then_escape(int x, char *err_msg, char **paths, char **cmd_arg);
int		open_file(char *path_to_file, int parent_process, int pipe_fd[2]);
void	close_fds(int pipe_fd[2], int flag);

#endif
