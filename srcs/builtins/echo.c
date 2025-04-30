/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 09:15:01 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_echo(t_env *cmds)
{
	int	j;
	int	n;

	j = 0;
	n = 1;
	while (cmds->arg[0] && cmds->arg[0][0] == '-'
		&& cmds->arg[0][1] == 'n' && cmds->arg[0][2] == '\0')
	{
		j++;
		n = 0;
	}
	j = 0;
	while (cmds->arg[j])
	{
		write(cmds->fd, cmds->arg[j], strlen(cmds->arg[j]));
		if (cmds->arg[j + 1])
			write(cmds->fd, " ", 1);
		j++;
	}
	if (n)
		write(cmds->fd, "\n", 1);
}
