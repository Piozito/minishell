/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:17:05 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/22 16:10:42 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*ptr2;

	i = 0;
	ptr = (char *)dest;
	ptr2 = (char *)src;
	while (i < n)
	{
		ptr[i] = ptr2[i];
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char teste[] = "batata";
	char teste2[] = "cozinha";
	char teste3[] = "batata";
	char teste4[] = "cozinha";

	ft_memcpy(teste, teste2, 9);

	printf("%s\n", teste);

	memcpy(teste3, teste4, 9);

	printf("%s\n", teste3);
}*/