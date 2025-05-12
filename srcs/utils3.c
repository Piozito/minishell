/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:26:40 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/09 20:21:42 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void ft_debug(t_env *cmd)
{
	if(cmd->path)
		printf("\033[0;32mpath is available.\033[0m\n");
	else
		printf("\033[0;31mpath has failed.\033[0m\n");
	if(cmd->env)
		printf("\033[0;32menv is available.\033[0m\n");
	else
		printf("\033[0;31menv has failed.\033[0m\n");
	if(cmd->exp)
		printf("\033[0;32mexport is available.\033[0m\n");
	else
		printf("\033[0;31mexport has failed.\033[0m\n");
    printf("-------------------------\n");
	printf("Command: %s\n", cmd->cmd);
    if (cmd->arg && cmd->arg[0] != NULL)
    {
        printf("Arguments:\n");
        for (int i = 0; cmd->arg[i] != NULL; i++)
        {
            printf("  Arg[%d]: %s\n", i, cmd->arg[i]);
        }
    }
    else
        printf("Arguments: None\n");
    printf("-------------------------\n");
}

void pop(t_env *cmds, int i)
{
	pid_t pid;
	int saved_stdin;
	int saved_stdout;

	if (cmd_check(cmds) == 0)
	{
		saved_stdin = dup(0);
		saved_stdout = dup(1);
		apply_fd(cmds);
		if(i == 0)
			check_builtin(cmds);
		dup2(saved_stdin, 0);
		dup2(saved_stdout, 1);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	pid = fork();
	if (pid == 0) 
	{
		apply_fd(cmds);
		if(i == 0)
			check_builtin(cmds);
	    exit(1);
	} 
	else if (pid > 0)
	    waitpid(pid, NULL, 0);
	else
	    perror("fork failed");
	return ; 
}

void check_errors(t_env *cmds)
{
	t_env *temp;

	temp = cmds;
	while(temp)
	{
		temp->path = my_get_path(temp);
		if(temp->path == NULL)
			printf("command not found: \"%s\"\n", temp->cmd);
		temp = temp->next;
	}
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if(*big == '\0')
		return NULL;
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
