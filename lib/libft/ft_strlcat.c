/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:06:04 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/29 15:52:29 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	if (size < i + 1)
		return (size + ft_strlen(src));
	while (src[j] != '\0' && i + 1 + j < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void)
{
	char	teste1[] = "Bom";
	char	teste2[] = " dia, rapaziada";
	char	c;

	printf("%li\n", ft_strlcat(teste1, teste2, 12));
	printf("%s\n", teste1);
}*/