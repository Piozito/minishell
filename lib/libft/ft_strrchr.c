/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:39:34 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/05/06 16:46:40 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptrsrc = s;
	char		*res;

	res = NULL;
	if (c > 255)
		c -= 256;
	while (*ptrsrc != '\0')
	{
		if (*ptrsrc == c)
			res = (char *)ptrsrc;
		ptrsrc++;
	}
	if (c == '\0')
		return ((char *)ptrsrc);
	return (res);
}
/*
#include <stdio.h>

int	main(void)
{
	char teste[] = "leite, bolachas e beca de leite(mimosa)";

	printf("%s", ft_strrchr(teste, 'e'));
} */