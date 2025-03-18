/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:39 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/29 17:33:19 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>

void	up(unsigned int i, char *str)
{
	printf("index = %d and %c\n", i, *str);
	if (*str >= 'a' && *str <= 'z')
		*str -= 32;
}

int	main(void)
{
	char str[] = "Boas pessoal";

	printf("Original string: %s\n", str);

	ft_striteri(str, &up);

	printf("%s\n", str);
	return (0);
} */