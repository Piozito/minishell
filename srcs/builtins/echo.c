/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/03/20 12:51:34 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int arg_c(char **args)
{
    int size;

    size = 0;
    while (args[size])
        size++;
    return (size);
}

int ft_echo(char **args)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if(arg_c(args) > 1)
    {
        if (args[1][0] == "-" && args[1][1] == "n")
        {
            n = 1;
            i++;
        }
        while (args[i])
        {
            ft_putstr_fd(args[i], 1);
            if (args[i + 1])
                write(1, " ", 1);
            i++;
        }
    }
    if (n == 0)
        write(1, "\n", 1);
    return (1);
}
