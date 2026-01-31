/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:03:13 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 15:03:15 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../../libft/libft.h"

void error_exit(const char *msg, int code);
void free_split(char **arr);
char **split_cmd(const char *s);
char *get_cmd_path(char *cmd, char **envp, int *perm_denied);
void exec_cmd(char *cmd_str, char **envp);

#endif
