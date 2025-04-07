/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:22:32 by fragarc2          #+#    #+#             */
/*   Updated: 2025/04/07 16:07:41 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int *get_key(char *arg)
{
	int key;

	key = 0;
	while (ft_strcmp(arg[key], "=") != 0)
		key++;
	return(key);
}

static char *ft_key(char *arg)
{
	char *key;
	int i;
	int j;

	j = 0;
	i = 0;
	while (ft_strcmp(arg[i], "=") != 0 && arg[i])
	{
		key = arg[i];
		i++;
	}
	return(key);
}

static char *ft_new(char *arg)
{
	char *key;
	int i;
	int j;

	j = 0;
	i = 0;
	while (ft_strcmp(arg[i], "=") != 0 && arg[i])
		i++;
	while (arg[i])
	{
		key[j] = arg[i];
		i++;
		j++;
	}
	return(key);
}

static int find_key(char *arg)
{
	int i;
	int j;
	extern char **environ;

	j = 0;
	i = 0;
	while (ft_strcmp(ft_key(environ[i]), arg) != 0 && environ[i])
		i++;
	if (ft_strcmp(ft_key(environ[i]), arg) != 0)
		return (0);
	return(i);
}

void	ft_$(t_env *cmds)
{
	int	i;
	int j;
	int k;
	int l;
	char *tmp;
	char *tmp2;
	extern char **environ;

	i = 0;
	k = 0;
	j = 0;
	l = 0;
	while (cmds->arg[i])
	{
		if (cmds->arg[i] == "$")
		{

			while(cmds->arg[i] != " ")
			{
				tmp2[l] = cmds->arg[i];
				l++;
				i++;
			}
			l = 0;
			while(tmp2[l])
			{
				tmp[k] = ((ft_new(environ[find_key(tmp2)]))[j]);
				k++;
				l++;
			}
		}
		tmp[k] = cmds->arg[i];
		k++;
		i++;
	}
}

