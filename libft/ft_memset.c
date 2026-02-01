/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:03:17 by esaleh            #+#    #+#             */
/*   Updated: 2025/05/23 09:09:45 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = c;
		s++;
		i++;
	}
	return (s - n);
}
/*

int	main(void)
{
	char str[50] = "Esmaeil Saleh is great!";
	printf("%s\n", str);
	ft_memset(str + 8, '.', 5*sizeof(char));
	printf("%s\n", str);
	return 0;
}
*/
