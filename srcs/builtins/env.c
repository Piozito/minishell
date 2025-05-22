/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/21 16:58:51 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int ft_env(t_env *cmds)
{
    int i = 0;
	if(cmds->arg[0] != NULL)
	{
		write(cmds->fd, "env: env doesn't accept flags or arguments.\n", 45);
		return(127);
	}
    while (cmds->env[i] != NULL)
	{
        write(cmds->fd, cmds->env[i], ft_strlen(cmds->env[i]));
		write(cmds->fd, "\n", 1);
		i++;
	}
	return(0);
}
