/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:56:36 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 09:20:06 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_env *cmds)
{
	int	exit_status;


	if (cmds->flag[0] == NULL && cmds->arg[1] == NULL)
	{
		if (cmds->arg[0])
		{
			if (!is_numeric(cmds->arg[0]))
				exit(2);
			exit_status = ft_atoi(cmds->arg[0]);
			if(exit_status > 255 || exit_status < 0)
			{
				printf("exit: Error codes must be less than 256.\n");
				return ;
			}
			exit(exit_status % 256);
		}
		exit(0);
	}
	else
		printf("exit: exit only accepts a positive integer less than 256 and no flags.\n");
}
