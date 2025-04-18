/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/16 15:17:53 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_pwd(t_env *cmds)
{
	char	cwd[1024];
	if (cmds->arg[0] != NULL || cmds->flag[0] != NULL)
	{
		printf("pwd: pwd doesn't accept flags or arguments.\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == 0)
		perror("pwd");
	printf("%s\n", cwd);
	return ;
}
