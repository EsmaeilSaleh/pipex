/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:04:13 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 16:56:59 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd_not_found(char *cmd, char **args, int perm_denied)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (perm_denied)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	free_split(args);
	if (perm_denied)
		exit(126);
	exit(127);
}

static void	execve_fail(char *cmd, char *path, char **args)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	perror(cmd);
	free(path);
	free_split(args);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

void	exec_cmd(char *cmd_str, char **envp)
{
	char	*path;
	char	**args;
	int		perm_denied;

	args = split_cmd(cmd_str);
	if (!args || !args[0])
	{
		free_split(args);
		exit(127);
	}
	perm_denied = 0;
	path = get_cmd_path(args[0], envp, &perm_denied);
	if (!path)
		cmd_not_found(args[0], args, perm_denied);
	execve(path, args, envp);
	execve_fail(args[0], path, args);
}

void	error_exit(const char *msg, int code)
{
	if (msg)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(msg);
	}
	exit(code);
}

void	free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
