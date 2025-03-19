/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:02:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/22 11:22:59 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
/*
#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	char test[] = "YOYO teste 1234 abcde";

	ft_putstr_fd(test, fd);
	close(fd);
}*/