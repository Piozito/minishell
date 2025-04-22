/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/22 12:13:14 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void ft_env(t_env *cmds, int fd)
{
    int i = 0;
	if(cmds->flag[0] != NULL || cmds->arg[0] != NULL)
	{
		write(fd, "env: env doesn't accept flags or arguments.\n", 45);
		return ;
	}
    while (cmds->env[i] != NULL)
	{
        write(fd, cmds->env[i], ft_strlen(cmds->env[i]));
		write(fd, "\n", 1);
		i++;
	}
}
