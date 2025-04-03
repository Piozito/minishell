/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:45 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/03 15:30:38 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_exec(char **exec_args, t_env *command, int arg_count)
{
	int	i;
	int	j;

	exec_args[0] = command->cmd;
	i = 0;
	while (command->flag[i] != NULL)
	{
		exec_args[i + 1] = command->flag[i];
		i++;
	}
	j = 0;
	while (command->arg[j] != NULL)
	{
		exec_args[i + 1] = command->arg[j];
		j++;
		i++;
	}
	exec_args[arg_count + 1] = NULL;
}

void	handle_fork_execution(char *path, char **exec_args, t_env *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(exec_args);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, exec_args, command->env) == -1)
		{
			perror("execve");
			free(exec_args);
			exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
}

int	counter(t_env *command)
{
	int	arg_count;
	int	i;

	arg_count = 0;
	while (command->arg[arg_count] != NULL)
		arg_count++;
	i = 0;
	while (command->flag[i] != NULL)
	{
		i++;
		arg_count++;
	}
	return (arg_count);
}

void	ft_exec(t_env *command)
{
	char	*path;
	int		arg_count;
	char	**exec_args;

	arg_count = counter(command);
	exec_args = malloc((arg_count + 2) * sizeof(char *));
	if (!exec_args)
	{
		perror("malloc");
		exit(1);
	}
	init_exec(exec_args, command, arg_count);
	path = my_get_path(command->cmd);
	if (path == NULL)
	{
		printf("command not found: \"%s\"\n", command->cmd);
		free(exec_args);
		return ;
	}
	handle_fork_execution(path, exec_args, command);
	free(exec_args);
	free(path);
}
