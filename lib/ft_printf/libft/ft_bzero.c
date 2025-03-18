/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:03:29 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/22 13:07:52 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char str[] = "batata";
	unsigned int i = 0;
	ft_bzero(str, 3);
	while (i < 6)
	{
		printf("%c\n", str[i]);
		i++;
	}
}*/