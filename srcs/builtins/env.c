/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:46:58 by marvin            #+#    #+#             */
/*   Updated: 2025/04/04 17:40:23 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"


void ft_env(t_env *cmds) {
    extern char **environ;
    char **env_snapshot = environ; // Take a snapshot
    int i = 0;

    (void)cmds;
    while (env_snapshot[i] != NULL) {
        printf("%s\n", env_snapshot[i]);
        i++;
    }
}
