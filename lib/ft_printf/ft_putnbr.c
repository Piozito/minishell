/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:25:26 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/12 10:48:06 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write(char *s, long k, int *counter)
{
	while (k >= 0)
	{
		write(1, s + k, 1);
		k--;
		(*counter)++;
	}
}

void	ft_putnbr(long long n, char *base, int *counter)
{
	int		k;
	int		temp;
	int		basel;
	char	s[22];

	basel = ft_strlen(base);
	k = 0;
	if (n <= 0)
	{
		if (n < 0)
			s[0] = '-';
		if (n == 0)
			s[0] = '0';
		ft_putchar(*s, counter);
	}
	while (n != 0)
	{
		if (n >= 0)
			temp = base[(n % basel)];
		else
			temp = base[((n % basel) * -1)];
		s[k++] = temp;
		n /= basel;
	}
	ft_write(s, (k - 1), counter);
}
