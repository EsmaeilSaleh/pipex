/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 08:10:00 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/01 08:10:00 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_escape(t_escape *e, size_t *i, char *dst, size_t *len)
{
	if (e->s[*i] != '\\' || e->quote == '\'')
		return (0);
	if (*i + 1 < e->end)
	{
		if (dst)
			dst[(*len)++] = e->s[*i + 1];
		else
			(*len)++;
		*i += 2;
		return (1);
	}
	if (dst)
		dst[(*len)++] = e->s[*i];
	else
		(*len)++;
	(*i)++;
	return (1);
}

static size_t	token_len(const char *s, size_t i, size_t end)
{
	size_t		len;
	t_escape	e;

	len = 0;
	e = (t_escape){s, end, 0};
	while (i < end)
	{
		if (handle_escape(&e, &i, NULL, &len))
			continue ;
		if (!e.quote && (s[i] == '\'' || s[i] == '"'))
			e.quote = s[i++];
		else if (e.quote && s[i] == e.quote)
		{
			e.quote = 0;
			i++;
		}
		else
			i += (len++ >= 0);
	}
	return (len);
}

static void	copy_token(char *dst, const char *s, size_t i, size_t end)
{
	size_t		len;
	t_escape	e;

	len = 0;
	e = (t_escape){s, end, 0};
	while (i < end)
	{
		if (handle_escape(&e, &i, dst, &len))
			continue ;
		if (!e.quote && (s[i] == '\'' || s[i] == '"'))
			e.quote = s[i++];
		else if (e.quote && s[i] == e.quote)
		{
			e.quote = 0;
			i++;
		}
		else
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

	j = skip_spaces(s, *i);
	if (!s[j])
		return ((*i = j), NULL);
	k = token_end(s, j);
	len = token_len(s, j, k);
	tok = ft_calloc(len + 1, sizeof(char));
	if (!tok)
		return ((*i = k), NULL);
	copy_token(tok, s, j, k);
	*i = k;
	return (tok);
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
