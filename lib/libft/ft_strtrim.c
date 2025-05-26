/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:27:04 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/26 15:28:12 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_verify(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (s1[i] != '\0' && (set_verify(s1[i], set) == 1))
		i++;
	while (s1[j - 1] != '\0' && (set_verify(s1[j - 1], set) == 1))
		j--;
	if (i - j == i)
		return (ft_calloc(1, 1));
	ptr = ft_substr(s1, (unsigned int)i, j - i);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char *strtrim;
	char s1[] = "-_-##-_-";
	strtrim = ft_strtrim(s1, " -_#");
	printf("%s", strtrim);
	return (0);
} */
