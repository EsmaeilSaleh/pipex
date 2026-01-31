/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:04:03 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 16:50:13 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_env(char **envp)
{
	size_t	i;

	if (!envp)
		return ("/usr/local/bin:/usr/bin:/bin"
			":/usr/sbin:/sbin");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return ("/usr/local/bin:/usr/bin:/bin"
			":/usr/sbin:/sbin");
}

static char	*find_in_path(char *cmd, char **paths, int *perm_denied)
{
	size_t	i;
	char	*tmp;
	char	*full;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (full && access(full, F_OK) == 0)
		{
			if (access(full, X_OK) == 0)
				return (full);
			if (perm_denied)
				*perm_denied = 1;
		}
		free(full);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp, int *perm_denied)
{
	char	*path_env;
	char	**paths;
	char	*full;

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
	path_env = get_path_env(envp);
	paths = ft_split(path_env, ':');
	full = find_in_path(cmd, paths, perm_denied);
	free_split(paths);
	return (full);
}
