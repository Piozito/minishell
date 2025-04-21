/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:01:44 by fragarc2         ###   ########.fr       */
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
        write(fd, cmds->env[i++], ft_strlen(cmds->env[i++]));
		write(fd, "\n", 1);

	}
}
