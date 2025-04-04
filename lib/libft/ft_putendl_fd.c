/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:40 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/22 11:23:03 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
/*
#include <fcntl.h>

int	main(void)
{
	int fd = open("test2.txt", O_WRONLY | O_CREAT, 0644);
	char test[] = "YOYO teste 1234 abcde";

	ft_putendl_fd(test, fd);
	close(fd);
}*/