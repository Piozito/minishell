/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 15:38:28 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ft_echo(t_env *cmds)
{
    int j;
    int n;

    j = 0;
    n = 1;
    if (cmds->arg[0] != NULL)
    {
        if (cmds->flag[0] != NULL && cmds->flag[0][0] != '\0')
        {
            if (cmds->flag[j] && cmds->flag[j][0] == '-' && cmds->flag[j][1] == 'n' && cmds->flag[j][2] == '\0')
                n = 0;
        }
        while (cmds->arg[j])
        {
            printf("%s", cmds->arg[j]);
            if (cmds->arg[j + 1] != NULL)
                printf(" ");
            j++;
        }
    }
    if (n == 1)
        printf("\n");
}
