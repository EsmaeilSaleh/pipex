/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 07:55:00 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/01 07:55:00 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static int	handle_escape(const char *s, size_t *i, char quote)
{
	if (s[*i] != '\\' || quote == '\'')
		return (0);
	if (s[*i + 1])
		*i += 2;
	else
		(*i)++;
	return (1);
}

size_t	skip_spaces(const char *s, size_t i)
{
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

size_t	token_end(const char *s, size_t i)
{
	char	quote;

	quote = 0;
	while (s[i])
	{
		if (!quote && is_space(s[i]))
			break ;
		if (handle_escape(s, &i, quote))
			continue ;
		if (!quote && (s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i++];
			continue ;
		}
		if (quote && s[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		i++;
	}
	return (i);
}
