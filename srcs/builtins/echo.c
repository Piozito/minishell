/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/06/05 15:22:34 by aaleixo-         ###   ########.fr       */
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
		write(1, cmds->arg[j], ft_strlen(cmds->arg[j]));
		if (cmds->arg[j + 1])
			write(1, " ", 1);
		j++;
	}
	if (n)
		write(1, "\n", 1);
	return (0);
}
