/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:09:27 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/12 10:48:16 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

int		ft_printf(const char *s, ...);
void	ft_putnbr(long long n, char *base, int *counter);
void	ft_putstr(char *str, int *counter);
void	ft_ptr(va_list args, int *counter);
char	ft_putchar(char c, int *counter);

#endif