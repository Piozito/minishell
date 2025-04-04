/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:10:59 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/22 16:14:16 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptrsrc;
	size_t	i;

	ptrsrc = (char *)s;
	i = 0;
	while (i < n)
	{
		if (*ptrsrc == (char)c)
			return (ptrsrc);
		ptrsrc++;
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char teste[] = "batata";
	printf("%s\n", ft_memchr(teste, 't', 4));
	printf("%s\n", memchr(teste, 't', 4));
}*/