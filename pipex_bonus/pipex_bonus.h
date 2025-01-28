/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:14:37 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/24 18:37:23 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define FD_MAX 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>

# define WRONG_ARGC "Wrong number of arguments"
# define NO_ENV "No environment variable"
# define ERR_MSG ": No such file or directory"
# define ERR_MSG_II "pipex: command not found: "
# define RADIX_X "0123456789"

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	char	specifier;
}	t_flags;

typedef struct s_fds
{
	int	i_fd;
	int	o_fd;
}	t_fds;

int			main(int argc, char **argv, char **env);

void		execute(char *command, char **env);
void		here_doc(char *limiter, int pipe_fd[2]);
char		*ft_getenv(const char *var, char **env);

int			ft_str_is_space(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);

void		release_memory(char **array);
void		escape(char *error_message, int x);
void		release_then_escape(int x, char *msg, char **paths, char **cmd_arg);
int			open_file(char *path_to_file, int parent_process, int pipe_fd[2]);

char		*get_next_line(int fd, char *limiter, int *i);
size_t		length_of(char *s, int newline_flag);
int			string_contains_newline(char *s);
char		*duplicate(char *s);
char		*concatenate(char *line, char *buffer);

void		initialize_flags(t_flags *flags);
const char	*parse_flags(const char *format, t_flags *flags);
int			ft_putnbr_base(int n, char *base);
int			digits_count(int n, int base_length);
int			specifier(char c);
int			ft_abs(int n);
int			padding_print(int padding, t_flags flags);
int			precision_print(int precision, int digits);
int			handle_d_and_i(int n, t_flags flags);
int			handle_c(char c, t_flags flags);
int			handle_s(const char *s, t_flags flags);
int			ft_printf(const char *format, ...);

#endif
