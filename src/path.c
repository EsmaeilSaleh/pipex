/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:04:03 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 16:46:16 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*default_path(void)
{
	return ("/usr/local/bin:/usr/bin:/bin"
		":/usr/sbin:/sbin");
}

static char	*get_path_env(char **envp)
{
	size_t	i;

	if (!envp)
		return ((char *)default_path());
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return ((char *)default_path());
}

static char	*handle_slash_cmd(char *cmd, int *perm_denied)
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
	char	*path_env;
	char	**paths;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_slash_cmd(cmd, perm_denied));
	path_env = get_path_env(envp);
	paths = ft_split(path_env, ':');
	full = find_in_path(cmd, paths, perm_denied);
	free_split(paths);
	return (full);
}
