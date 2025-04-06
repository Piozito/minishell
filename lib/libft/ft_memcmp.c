/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:27:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/05/06 16:44:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	i = 0;
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (((i + 1) < n) && (ptrs1[i] == ptrs2[i]))
		i++;
	return (ptrs1[i] - ptrs2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	char teste[] = "batata";
	char teste2[] = "banana";
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	printf("%i\n", ft_memcmp(s2, s3, 4));
	printf("%i\n", memcmp(s2, s3, 4));

	printf("%i\n", ft_memcmp(teste, teste2, 5));
	printf("%i\n", memcmp(teste, teste2, 5));
} */