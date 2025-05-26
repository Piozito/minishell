/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:19:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/23 17:41:19 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void free_more(char **str, char **str2)
{
	free_subtokens(str);
	free_subtokens(str2);
}

char	*my_get_path(t_env *cmds)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	if (!access(cmds->cmd, X_OK))
		return (cmds->cmd);
	if (cmds->cmd[0] == '/' || (cmds->cmd[0] == '.' && cmds->cmd[1] == '/'))
		return (ft_strdup(cmds->cmd));
	i = -1;
	allpath = ft_split(cmds->path, ':');
	s_cmd = ft_split(cmds->cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_more(s_cmd, allpath);
			return (exec);
		}
		free(exec);
	}
	free_more(s_cmd, allpath);
	return (NULL);
}

void execute_child(char *path, char **exec_args, t_env *command)
{
    if (execve(path, exec_args, command->env) == -1)
    {
        command_not_found(command->cmd);
        free(exec_args);
        command->exit_status = 127;
        exit(127);
    }
}

int handle_parent(pid_t pid, t_env *cmds)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        cmds->exit_status = WEXITSTATUS(status);
    else
        cmds->exit_status = 1;
		duping(cmds);
    return cmds->exit_status;
}

void duping(t_env *cmds)
{
	dup2(cmds->saved_stdin, 0);
	dup2(cmds->saved_stdout, 1);
	close(cmds->saved_stdin);
	close(cmds->saved_stdout);
}
