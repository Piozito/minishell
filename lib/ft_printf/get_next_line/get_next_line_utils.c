/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:53:35 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/03/09 16:08:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_count_word(char *s)
{
	int	len;

	len = 0;
	while (s && s[len])
	{
		if (s[len] == '\n')
			return (len + 1);
		len++;
	}
	return (len);
}

void	*ft_clean(char *buf, int *newline, int funct)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*newline = 0;
	if (funct <= 0)
	{
		free(buf);
		return (NULL);
	}
	while (i < BUFFER_SIZE && buf[i] != '\0')
	{
		if (*newline == 1 && funct == 2)
			buf[j++] = buf[i];
		if (buf[i] == '\n' && funct == 2)
			*newline = 1;
		buf[i] = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	len1 = ft_count_word(s1);
	len2 = ft_count_word(s2);
	s3 = (char *)malloc(len1 + len2 + 1);
	if (!s3)
		return (s1);
	i = -1;
	while (++i < len1)
		s3[i] = s1[i];
	j = 0;
	while (j < len2)
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	free(s1);
	return (s3);
}

char	*ft_count(char *buf, int *newline, char *line)
{
	line = ft_strjoin_gnl(line, buf);
	if (!line)
		return (NULL);
	ft_clean(buf, newline, 2);
	return (line);
}
