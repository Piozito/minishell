/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:19:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/05 19:31:14 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_more(char **str, char **str2)
{
	free_subtokens(str);
	free_subtokens(str2);
}

int	check_exec(char *exec, char **allpath)
{
	if (access(exec, F_OK | X_OK) == 0)
	{
		free_subtokens(allpath);
		return (0);
	}
	return (1);
}

char	*my_get_path(t_env *cmds)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	*path;

	if (cmds->cmd && !access(cmds->cmd, X_OK))
		return (cmds->cmd);
	i = -1;
	path = env_expander(cmds, "PATH=");
	allpath = ft_split(path, ':');
	free(path);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmds->cmd);
		free(path_part);
		if (cmds->cmd && check_exec(exec, allpath) == 0)
			return (exec);
		free(exec);
	}
	free_subtokens(allpath);
	return (NULL);
}

void	execute_child(char *path, char **exec_args, t_env *command)
{
	int	exit_st;

	if (execve(path, exec_args, command->env) == -1)
	{
		command_not_found(command);
		free(exec_args);
		exit_st = command->exit_status;
		ft_clear(command);
		exit(exit_st);
	}
}

int	handle_parent(pid_t pid, t_env *cmds)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmds->exit_status = WEXITSTATUS(status);
	else
		cmds->exit_status = 1;
	duping(cmds);
	return (cmds->exit_status);
}
