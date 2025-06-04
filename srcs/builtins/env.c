/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:06:17 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_env(t_env *cmds)
{
	int	i;

	i = 0;
	if (env_tester(cmds) == 1)
		return (126);
	if (cmds->arg[0] != NULL)
	{
		write(cmds->fd, "env: env doesn't accept flags or arguments.\n", 45);
		return (127);
	}
	while (cmds->env[i] != NULL)
	{
		write(cmds->fd, cmds->env[i], ft_strlen(cmds->env[i]));
		write(cmds->fd, "\n", 1);
		i++;
	}
	return (0);
}
