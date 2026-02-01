/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 07:55:00 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/01 07:55:00 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	token_len(const char *s, size_t i, size_t end)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (i < end)
	{
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
		len++;
		i++;
	}
	return (len);
}

static void	copy_token(char *dst, const char *s, size_t i, size_t end)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (i < end)
	{
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
		dst[len++] = s[i++];
	}
	dst[len] = '\0';
}

static char	*dup_token(const char *s, size_t *i)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	*tok;

	j = *i;
	j = skip_spaces(s, j);
	if (!s[j])
	{
		*i = j;
		return (NULL);
	}
	k = token_end(s, j);
	len = token_len(s, j, k);
	tok = ft_calloc(len + 1, sizeof(char));
	if (!tok)
	{
		*i = k;
		return (NULL);
	}
	copy_token(tok, s, j, k);
	*i = k;
	return (tok);
}

size_t	count_tokens(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		count++;
		i = token_end(s, i);
	}
	return (count);
}

int	build_tokens(char **out, const char *s, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < count)
	{
		out[j] = dup_token(s, &i);
		if (!out[j])
		{
			free_split(out);
			return (0);
		}
		j++;
	}
	out[j] = NULL;
	return (1);
}
