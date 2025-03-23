/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 19:56:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int is_numeric(const char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void exit_builtin(char **args)
{
    int exit_status;

    if (args[1])
    {
        if (!is_numeric(args[1]))
            exit(2);
        if (args[2])
            return ;
        exit_status = ft_atoi(args[1]);
        exit(exit_status % 256);
    }
    exit(0);
}