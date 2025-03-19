/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:37:03 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/04/24 10:26:14 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

long long	abs_val(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	unsigned int	sign;
	unsigned int	len;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = nbr_len(n);
	str = str_new(len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	nbr = abs_val(n);
	while (len--)
	{
		str[len] = 48 + nbr % 10;
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int nbr = -2147483648;

	char *result = ft_itoa(nbr);
	printf("%s\n", result);
	free(result);
	return (0);
}*/