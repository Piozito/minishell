/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 16:04:46 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_echo(t_env *cmds)
{
	int	j;
	int	n;

	j = 0;
	n = 1;
	while (cmds->flag[j] && cmds->flag[j][0] == '-'
		&& cmds->flag[j][1] == 'n' && cmds->flag[j][2] == '\0')
	{
		j++;
		n = 0;
	}
	while (cmds->flag[j])
	{
		write(cmds->fd, cmds->flag[j], strlen(cmds->flag[j]));
		write(cmds->fd, " ", 1);
		j++;
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
