/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 19:22:34 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_echo(t_env *cmds)
{
	int	j;
	int	n;

	j = 0;
	n = 1;
	while (cmds->flag[j])
	{
		if (cmds->flag[0] && cmds->flag[0][0] == '-'
		&& cmds->flag[0][1] == 'n'
		&& cmds->flag[0][2] == '\0')
			n = 0;
		else
			printf("%s ", cmds->flag[j]);
		j++;
	}
	j = 0;
	while (cmds->arg[j])
	{
		printf("%s", cmds->arg[j]);
		if (cmds->arg[j + 1] != NULL)
			printf(" ");
		j++;
	}
	if (n == 1)
		printf("\n");
}
