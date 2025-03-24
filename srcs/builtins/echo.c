/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 12:17:30 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int arg_c(char **args)
{
    int size;

    size = 0;
    while (args[size])
        size++;
    return (size);
}

void ft_echo(char **args)
{
	int j;
    int n;

	j = 1;
    n = 1;
    if(arg_c(args) > 1)
    {
        if (args[j][0] == '-' && args[j][1] == 'n' 
		&& args[j][2] == '\0')
        {
            n = 0;
			j++;
        }
        while (args[j])
        {
            printf("%s", args[j]);
            if (args[j + 1])
                printf(" ");
            j++;
        }
    }
    if (n == 1)
        printf("\n");
}
