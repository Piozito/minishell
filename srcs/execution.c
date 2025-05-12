/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:45 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/12 18:10:41 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_exec(char **exec_args, t_env *command, int arg_count)
{
	int	i;

	exec_args[0] = command->cmd;
	i = 0;
	while (command->arg[i] != NULL)
	{
		exec_args[i + 1] = command->arg[i];
		i++;
	}
	exec_args[arg_count + 1] = NULL;
}

void	handle_fork_execution(char *path, char **exec_args, t_env *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(exec_args);
		exit(1);
	}
	else if (pid == 0)
	{
		if(cmd_check(command) == 0 && ft_isalpha(command->cmd[0]) == 0)
		{
			printf("command not found: \"%s\"\n", command->cmd);
			free(exec_args);
			exit(127);
		}
		else if (execve(path, exec_args, command->env) == -1)
		{
			printf("command not found: \"%s\"\n", command->cmd);
			free(exec_args);
			exit(127);
		}
	}
	else
		waitpid(pid, &command->exit_status, 0);
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
		perror("malloc");
		return (1);
	}
	init_exec(exec_args, command, arg_count);
	command->path = my_get_path(command);
	if (command->path == NULL)
	{
		printf("command not found: \"%s\"\n", command->cmd);
		free(exec_args);
		return (127);
	}
	handle_fork_execution(command->path, exec_args, command);
	free(exec_args);
	return (0);
}