/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:26:40 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/20 11:15:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_debug(t_env *cmd)
{
	int	i;

	i = 0;
	if (cmd->path)
		printf("\033[0;32mpath is available.\033[0m\n");
	else
		printf("\033[0;31mpath has failed.\033[0m\n");
	if (cmd->env)
		printf("\033[0;32menv is available.\033[0m\n");
	else
		printf("\033[0;31menv has failed.\033[0m\n");
	if (cmd->exp)
		printf("\033[0;32mexport is available.\033[0m\n");
	else
		printf("\033[0;31mexport has failed.\033[0m\n");
	printf("-------------------------\nCommand: \"%s\"\n", cmd->cmd);
	if (cmd->arg[0] != NULL)
	{
		printf("Arguments:\n");
		while (cmd->arg[i] != NULL)
		{
			printf("	Arg[%d]: \"%s\"\n", i, cmd->arg[i]);
			i++;
		}
	}
	else
		printf("Arguments: None\n");
	printf("-------------------------\n");
}

int pop(t_env *cmds, int i)
{
    pid_t pid;

    if (cmd_check(cmds) == 0)
    {
        if(apply_fd(cmds) == 1)
            return(1);
        if (i == 0)
            cmds->exit_status = check_builtin(cmds);
		duping(cmds);
        return 0;
    }
    pid = fork();
    if (pid == 0)
    {
        if(apply_fd(cmds) == 1)
            exit(1);
        if (i == 0)
            exit(check_builtin(cmds));
        exit(1);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            cmds->exit_status = WEXITSTATUS(status);
        else
            cmds->exit_status = 1;
    }
	else
		perror("fork failed");
	duping(cmds);
    return cmds->exit_status;
}

void	check_errors(t_env *cmds)
{
	t_env	*temp;

	temp = cmds;
	while (temp)
	{
		temp->path = my_get_path(temp);
		if (temp->path == NULL)
			command_not_found(cmds->cmd);
		temp = temp->next;
	}
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

void command_not_found(char *cmd)
{
	write(2, "command not found: \"", 20);
	ft_putstr_fd(cmd, 2);
	write(2, "\"\n", 2);
}

int executable_check(t_env *cmds)
{
	int i = 0;
	if(!cmds->cmd)
	{
		if(ft_strncmp(cmds->arg[0], ">", 1) == 0 || ft_strncmp(cmds->arg[1], "<", 1) == 0)
			apply_fd(cmds);
		return 1;
	}
	while(cmds->cmd[i])
	{
		if(ft_isalpha(cmds->cmd[i]) == 1)
			return 0;
		i++;
	}
	return 1;
}