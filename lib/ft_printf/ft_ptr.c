/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:11:37 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/12 10:57:55 by aaleixo-         ###   ########.fr       */
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

void	ft_putnbr_ptr(unsigned long long n, char *base, int *counter)
{
	int		k;
	int		temp;
	int		baselen;
	char	s[22];

	baselen = ft_strlen(base);
	k = 0;
	while (n != 0)
	{
		temp = base[(n % baselen)];
		s[k++] = temp;
		n /= baselen;
	}
	ft_write(s, (k - 1), counter);
}

void	ft_ptr(va_list args, int *counter)
{
	unsigned long long	ptr;

	ptr = va_arg(args, unsigned long long);
	if (ptr == 0)
		ft_putstr("(nil)", counter);
	else
	{
		ft_putstr("0x", counter);
		ft_putnbr_ptr(ptr, "0123456789abcdef", counter);
	}
}
