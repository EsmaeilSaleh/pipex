/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:03:55 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 16:41:12 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_cmd(const char *s)
{
	char	**out;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	out = ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	if (!build_tokens(out, s, count))
		return (NULL);
	return (out);
}
