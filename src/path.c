/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:04:03 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 15:04:06 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static char	*find_in_path(char *cmd, char **paths, int *perm_denied)
{
	size_t	i;
	char	*full;

	i = 0;
	while (paths && paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, F_OK) == 0)
		{
			if (access(full, X_OK) == 0)
				return (full);
			*perm_denied = 1;
		}
		free(full);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp, int *perm_denied)
{
	size_t	i;
	char	*path_env;
	char	**paths;
	char	*full;
	const char	*default_path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			if (perm_denied)
				*perm_denied = 1;
		}
		return (NULL);
	}
	if (!envp)
		path_env = (char *)default_path;
	i = 0;
	path_env = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		path_env = (char *)default_path;
	paths = ft_split(path_env, ':');
	full = find_in_path(cmd, paths, perm_denied);
	free_split(paths);
	return (full);
}
