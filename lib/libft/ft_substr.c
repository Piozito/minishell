/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:09:43 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/05/07 13:36:48 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*hay;
	char	*ptr;

	i = -1;
	hay = (char *)s;
	if (ft_strlen(s) < start)
		return (ft_calloc(1, 1));
	else if (s[start + 1] == '\0')
		ptr = (char *)malloc(2);
	else if (len < (ft_strlen(s) + 1))
		ptr = (char *)malloc(len + 1);
	else
		ptr = (char *)malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[++i] != '\0' && i < len && s[start] != '\0')
		ptr[i] = hay[start + i];
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char *sub = ft_substr("boas boas ", 0, 99999);

	printf("%s\n", sub);
	free(sub);
	return (0);
} */