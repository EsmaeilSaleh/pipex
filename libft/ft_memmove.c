/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:36:19 by esaleh            #+#    #+#             */
/*   Updated: 2025/06/02 12:15:48 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	return (dest);
}
/*
#include <stdio.h>
void	*ft_memmove(void *dest, void *src, size_t n)
{
	size_t	i;
	size_t	arr[50];
	i = 0;
	while (i < n)
	{
		arr[i] = *(char *)src;
		src++;
		i++;
	}
	i = 0;
	while (i < n)
	{
		*(char *)dest = arr[i];
		dest++;
		i++;
	}
	return (dest - n);
}
*/
