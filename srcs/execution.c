/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:45 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 14:59:37 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_exec(char **exec_args, t_env *command, int arg_count)
{
	int	i;

	i = 0;
	exec_args[0] = command->cmd;
	while (command->arg[i] != NULL)
	{
		exec_args[i + 1] = command->arg[i];
		i++;
	}
	exec_args[arg_count + 1] = NULL;
}

int	handle_fork(char *path, char **exec_args, t_env *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		write(0, "fork", 5);
		free(exec_args);
		command->exit_status = 1;
		return (command->exit_status);
	}
	else if (pid == 0)
	{
		execute_child(path, exec_args, command);
		exit(127);
	}
	else
		return (handle_parent(pid, command));
}

int	counter(t_env *command)
{
	int	arg_count;

	arg_count = 0;
	while (command->arg[arg_count] != NULL)
		arg_count++;
	return (arg_count);
}

int	ft_exec(t_env *command)
{
	int		arg_count;
	char	**exec_args;

	arg_count = counter(command);
	exec_args = malloc((arg_count + 2) * sizeof(char *));
	if (!exec_args)
	{
		write(2, "malloc", 7);
		return (1);
	}
	if (env_tester(command) == 0)
	{
		init_exec(exec_args, command, arg_count);
		if (command->path == NULL)
		{
			command_not_found(command);
			free(exec_args);
			return (command->exit_status);
		}
		command->exit_status = handle_fork(command->path, exec_args, command);
	}
	else
		command->exit_status = 126;
	free(exec_args);
	return (command->exit_status);
}
