/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:45:15 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/29 15:38:11 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (p);
}
/*
#include <stdio.h>

int	main(void)
{
	char src[] = "Panquecas com chocolate";
	char *dest;
	int arg;

	dest = src + 1;
	ft_memset(dest, 'c', 6);
	printf("%s\n", dest);
	memset(dest, 'c', 6);
	printf("%s\n", dest);
	return (0);
} */