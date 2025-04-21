/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:57:44 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 15:24:38 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if(!ptr)
		return NULL;
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char src[] = "Panquecas com chocolate";
	char *dest;
	char *dest2;
	int arg;

	dest = ft_strdup(src);
	printf("%s\n", dest);
	dest2 = strdup(src);
	printf("%s\n", dest2);
	return (0);
} */