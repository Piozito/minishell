/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:40:17 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 19:09:47 by fragarc2         ###   ########.fr       */
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
	ft_strlcpy(new[2], "PWD=", 5);
	ft_strlcat(new[2], cwd, ft_strlen(cwd) + ft_strlen(new[2]) + 1);
	free(cwd);
	new[3] = NULL;
	return (new);
}

void	ft_cmds_free(t_env *cmds, int ex)
{
	t_env	*tmp;
	t_env	*next;

	tmp = cmds;
	if (ex == 1)
	{
		rl_clear_history();
		free_subtokens(tmp->exp);
		free_subtokens(tmp->env);
	}
	duping(tmp);
	while (tmp)
	{
		next = tmp->next;
		if (tmp->cmd && tmp->cmd != tmp->path)
			free(tmp->cmd);
		if (tmp->path)
			free(tmp->path);
		free_subtokens(tmp->arg);
		if (ex == 1 || tmp->prev)
			free(tmp);
		tmp = next;
	}
}

int	ft_clear(t_env *cmds)
{
	t_env	*temp;
	int		exit_code;

	temp = cmds;
	while (temp && temp->prev)
		temp = temp->prev;
	exit_code = temp->exit_status;
	ft_cmds_free(temp, 1);
	return (exit_code);
}

void	ft_putenv(t_env *cmds, char *var)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (cmds->env[i])
	{
		if (ft_strncmp(var, "OLDPWD=", 7) == 0
			&& ft_strncmp(cmds->env[i], "OLDPWD=", 7) == 0)
		{
			free(cmds->env[i]);
			cmds->env[i] = ft_strdup(var);
		}
		else if (ft_strncmp(var, "PWD=", 4) == 0
			&& ft_strncmp(cmds->env[i], "PWD=", 4) == 0)
		{
			free(cmds->env[i]);
			cmds->env[i] = ft_strdup(var);
		}
		i++;
	}
}

char	*ft_envstrchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
		{
			str++;
			return (ft_strdup(str));
		}
		str++;
	}
	return (ft_strdup(""));
}
