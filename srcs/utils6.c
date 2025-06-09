/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:40:17 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 13:25:56 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**fake_env_creator(void)
{
	char	**new;
	char	*cwd;

	new = (char **)malloc(4 * sizeof(char *));
	if (!new)
		general_error("env malloc failed.", 0, 1, NULL);
	new[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!new[0])
		general_error("env malloc failed.", 0, 1, NULL);
	new[1] = ft_strdup("SHLVL=1");
	if (!new[1])
		general_error("env malloc failed.", 0, 1, NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		general_error("getcwd failed.", 0, 1, NULL);
	new[2] = (char *)malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
	if (!new[2])
		general_error("env malloc failed.", 0, 1, NULL);
	ft_strlcpy(new[2], "PWD=", 4);
	ft_strlcat(new[2], cwd, ft_strlen(cwd));
	free(cwd);
	new[3] = NULL;
	return (new);
}

void	ft_clear(t_env *cmds)
{
	t_env *temp;

	temp = cmds;
	while(temp && temp->prev)
		temp = temp->prev;
	ft_cmds_free(temp, 1);
}
