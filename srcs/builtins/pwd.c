/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:40 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/04 09:15:27 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void	ft_pwd(t_env *cmds)
{
	char	cwd[MAX_PATH];

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
