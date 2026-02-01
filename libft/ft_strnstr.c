/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 02:23:32 by esaleh            #+#    #+#             */
/*   Updated: 2025/05/28 15:08:40 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
/*
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		while (*big == *little && i < len)
		{
			big++;
			little++;
			i++;
		}
		if (i == len)
			return ((char *)big - len);
		big++;
	}
	return (0);
}
*/
/*
#include <stdio.h>

int	main(void)
{
	const char *largestring = "ipsum dolor sit lorem ipsum dolor";
	const char *smallstring = "sit";
	char *ptr;

	ptr = ft_strnstr(largestring, smallstring, 4);
	printf("%s\n", ptr);

	return (0);
}
*/
