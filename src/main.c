/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:03:36 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 15:03:38 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_in(char **argv, char **envp, int pipefd[2])
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit(argv[1], 1);
	if (dup2(infile, STDIN_FILENO) < 0)
		error_exit("dup2", 1);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_exit("dup2", 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	exec_cmd(argv[2], envp);
}

static void	child_out(char **argv, char **envp, int pipefd[2])
{
	int	outfile;

	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit(argv[4], 1);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error_exit("dup2", 1);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		error_exit("dup2", 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	exec_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status2;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile",
			STDERR_FILENO);
		return (1);
	}
	if (pipe(pipefd) < 0)
		error_exit("pipe", 1);
	pid1 = fork();
	if (pid1 < 0)
		error_exit("fork", 1);
	if (pid1 == 0)
		child_in(argv, envp, pipefd);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("fork", 1);
	if (pid2 == 0)
		child_out(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}
