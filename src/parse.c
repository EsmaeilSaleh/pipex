/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:03:55 by esaleh            #+#    #+#             */
/*   Updated: 2026/01/31 15:03:57 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static size_t	count_tokens(const char *s)
{
	size_t	i;
	size_t	count;
	char	q;

	i = 0;
	count = 0;
	q = 0;
	while (s && s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		q = 0;
		while (s[i] && (q || !is_space(s[i])))
		{
			if (s[i] == '\\' && s[i + 1] && q != '\'')
				i += 2;
			else if ((s[i] == '\'' || s[i] == '"') && q == 0)
				q = s[i++];
			else if (s[i] == q)
			{
				q = 0;
				i++;
			}
			else
				i++;
		}
	}
	return (count);
}

static char	*build_token(const char *s, size_t *i)
{
	char	*buf;
	size_t	j;
	char	q;

	buf = (char *)malloc(ft_strlen(s) + 1);
	if (!buf)
		return (NULL);
	j = 0;
	q = 0;
	while (s[*i] && is_space(s[*i]))
		(*i)++;
	while (s[*i] && (q || !is_space(s[*i])))
	{
		if (s[*i] == '\\' && s[*i + 1] && q != '\'')
		{
			buf[j++] = s[*i + 1];
			*i += 2;
		}
		else if ((s[*i] == '\'' || s[*i] == '"') && q == 0)
			q = s[(*i)++];
		else if (s[*i] == q)
		{
			q = 0;
			(*i)++;
		}
		else
			buf[j++] = s[(*i)++];
	}
	buf[j] = '\0';
	return (buf);
}

char	**split_cmd(const char *s)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	**out;

	count = count_tokens(s);
	out = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		out[j] = build_token(s, &i);
		if (!out[j])
		{
			free_split(out);
			return (NULL);
		}
		j++;
	}
	out[j] = NULL;
	return (out);
}
