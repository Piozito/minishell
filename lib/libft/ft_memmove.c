/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:37:25 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/29 15:34:33 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char	*ptrsrc;
	unsigned char		*ptrdest;
	size_t				i;

	ptrsrc = (unsigned const char *)src;
	ptrdest = (unsigned char *)dest;
	i = 0;
	if (ptrdest > ptrsrc)
	{
		while (n-- > 0)
			ptrdest[n] = ptrsrc[n];
	}
	else
	{
		while (i < n)
		{
			ptrdest[i] = ptrsrc[i];
			i++;
		}
	}
	return (ptrdest);
}
/*
#include <stdio.h>

int	main(void)
{
	char src[] = "Panquecas com chocolate";
	char *dest;
	int arg;

	dest = src + 1;
	ft_memmove(dest, "Banana", 6);
	printf("%s\n", dest);
	memmove(dest, "Banana", 6);
	printf("%s\n", dest);
	return (0);
} */