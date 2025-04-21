/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 15:29:55 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_echo(t_env *cmds, int fd)
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
		write(fd, cmds->flag[j], strlen(cmds->flag[j]));
		write(fd, " ", 1);
		j++;
	}
	j = 0;
	while (cmds->arg[j])
	{
		write(fd, cmds->arg[j], strlen(cmds->arg[j]));
		if (cmds->arg[j + 1])
			write(fd, " ", 1);
		j++;
	}
	if (n)
		write(fd, "\n", 1);
}
