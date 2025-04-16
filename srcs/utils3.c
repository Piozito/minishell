/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:26:40 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/16 15:24:45 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void ft_debug(t_env *cmd)
{
	if(cmd->path)
		printf("\033[0;32mpath is available.\033[0m\n");
	else
		printf("\033[0;31mpath has failed.\033[0m\n");
    printf("-------------------------\n");
	printf("Command: %s\n", cmd->cmd);
    if (cmd->flag && cmd->flag[0] != NULL)
    {
        printf("Flags:\n");
        for (int i = 0; cmd->flag[i] != NULL; i++)
        {
            printf("  Flag[%d]: %s\n", i, cmd->flag[i]);
        }
    }
    else
        printf("Flags: None\n");
    if (cmd->arg && cmd->arg[0] != NULL)
    {
        printf("Arguments:\n");
        for (int i = 0; cmd->arg[i] != NULL; i++)
        {
            printf("  Arg[%d]: %s\n", i, cmd->arg[i]);
        }
    }
    else
        printf("Arguments: None\n");
    printf("-------------------------\n");
}
