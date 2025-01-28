/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bis_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:16:37 by yabokhar          #+#    #+#             */
/*   Updated: 2025/01/21 21:29:09 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_getenv(const char *var, char **env);
void	execute(char *command, char **env);

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
	release_then_escape(1, ft_strjoin(ERR_MSG_II, command), paths, cmd_args);
}
