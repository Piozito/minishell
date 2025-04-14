/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:46:58 by marvin            #+#    #+#             */
/*   Updated: 2025/04/14 14:25:52 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ft_env(t_env *cmds)
{
    extern char **environ;
    char **env_snapshot = environ;
    int i = 0;
	if(cmds->flag[0] != NULL || cmds->arg[0] != NULL)
	{
		printf("env: env doesn't accept flags or arguments.\n");
		return ;
	}
    while (env_snapshot[i] != NULL)
        printf("%s\n", env_snapshot[i++]);
}
