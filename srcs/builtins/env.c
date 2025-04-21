/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 12:04:45 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ft_env(t_env *cmds)
{
    int i = 0;
	if(cmds->flag[0] != NULL || cmds->arg[0] != NULL)
	{
		printf("env: env doesn't accept flags or arguments.\n");
		return ;
	}
    while (cmds->env[i] != NULL)
        printf("%s\n", cmds->env[i++]);
}
