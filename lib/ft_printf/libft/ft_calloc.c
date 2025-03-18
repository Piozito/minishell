/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:27:11 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/05/09 14:52:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (size > 0)
	{
		if ((nmemb > (18446744073709551615UL / size)) && size > 0)
			return (NULL);
	}
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char *teste = calloc(5, 1);
	ft_strlcpy(teste, "bora", 5);

	printf("%s\n", teste);
	free(teste);
}*/