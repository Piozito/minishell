/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:48:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/29 15:59:57 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t				i;
	unsigned char		*ptrdest;
	unsigned const char	*ptrsrc;

	i = 0;
	ptrdest = (unsigned char *)dst;
	ptrsrc = (unsigned const char *)src;
	if (size == 0)
		return (ft_strlen(src));
	while ((size - 1) > i && src[i])
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	ptrdest[i] = '\0';
	i = 0;
	while (ptrsrc[i] != '\0')
		i++;
	return (i);
}

/* #include <stdio.h>

int	main(void)
{
	char teste1[] = "Bom dia, rapaziada";
	char teste2[] = "Mau dia, rapazes";
	size_t resultado = ft_strlcpy(teste2, teste1, 6);

	printf("%s %zu\n", teste2, resultado);
} */