/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:46:58 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 12:16:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

void    ft_env(t_env *mini)
{
    int     i;
    char    **env;

    i = 0;
    env = mini->env;
    while (env[i])
    {
        write(1, env[i], ft_strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }
}