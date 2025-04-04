/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:46:58 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 10:30:42 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_env(t_env *cmds)
{
	int	i;

	i = 0;
	if(cmds->arg[0] == NULL && cmds->flag[0] == NULL)
	{
		while (cmds->env[i])
		{
			printf("%s\n", cmds->env[i]);
			i++;
		}
	}
	else
		printf("env: env doesn't accept flags or arguments.\n");
}
