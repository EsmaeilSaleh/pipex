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

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static size_t	count_tokens(const char *s)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		quote = 0;
		while (s[i])
		{
			if (!quote && is_space(s[i]))
				break ;
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
	}
	return (count);
}

static char	*dup_token(const char *s, size_t *i)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	quote;
	char	*tok;

	j = *i;
	while (s[j] && is_space(s[j]))
		j++;
	if (!s[j])
	{
		*i = j;
		return (NULL);
	}
	k = j;
	len = 0;
	quote = 0;
	while (s[k])
	{
		if (!quote && is_space(s[k]))
			break ;
		if (!quote && (s[k] == '\'' || s[k] == '"'))
		{
			quote = s[k++];
			continue ;
		}
		if (quote && s[k] == quote)
		{
			quote = 0;
			k++;
			continue ;
		}
		len++;
		k++;
	}
	tok = ft_calloc(len + 1, sizeof(char));
	if (!tok)
	{
		*i = k;
		return (NULL);
	}
	len = 0;
	quote = 0;
	while (j < k)
	{
		if (!quote && (s[j] == '\'' || s[j] == '"'))
		{
			quote = s[j++];
			continue ;
		}
		if (quote && s[j] == quote)
		{
			quote = 0;
			j++;
			continue ;
		}
		tok[len++] = s[j++];
	}
	tok[len] = '\0';
	*i = k;
	return (tok);
}

char	**split_cmd(const char *s)
{
	char	**out;
	size_t	count;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	out = ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		out[j] = dup_token(s, &i);
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
