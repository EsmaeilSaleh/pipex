/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:48:45 by esaleh            #+#    #+#             */
/*   Updated: 2025/05/28 15:11:31 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s)
	{
		if (*s == (char)c)
			tmp = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (tmp);
}

/*
char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	a;

	a = 'a';
	tmp = &a;
	while (*s)
	{
		if (*s == c)
			tmp = (char *)s;
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	if (tmp != &a)
		return (tmp);
	return (0);
}
*/
/*
#include <stdio.h>

int	main(void)
{
	const char str[] = "Hello, World!";
	const char ch = 's';

	// Search in the substring "World!"
	char* ptr = ft_strrchr(str + 7, ch); 

	if (ptr) {
		printf("'%c' found at position %ld\n", ch, ptr - str);
	} else {
		printf("'%c' not found in the substring\n", ch);
	}

	return 0;
}
*/
