/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 16:28:42 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_echo(t_env *cmds)
{
	int	j;
	int	n;

	j = 0;
	n = 1;
	while (cmds->arg[j] && cmds->arg[j][0] == '-'
		&& cmds->arg[j][1] == 'n' && cmds->arg[j][2] == '\0')
	{
		j++;
		n = 0;
	}
	while (cmds->arg[j])
	{
		write(cmds->fd, cmds->arg[j], strlen(cmds->arg[j]));
		if (cmds->arg[j + 1])
			write(cmds->fd, " ", 1);
		j++;
	}
	if (n)
		write(cmds->fd, "\n", 1);
	return (0);
}
