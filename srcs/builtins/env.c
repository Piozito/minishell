/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:46:58 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 11:47:10 by aaleixo-         ###   ########.fr       */
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
