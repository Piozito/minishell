/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils3.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/15 15:26:40 by aaleixo-		  #+#	#+#			 */
/*   Updated: 2025/05/21 12:17:03 by aaleixo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_debug(t_env *cmd)
{
	int	i;

	i = -1;
	if (cmd->env)
		printf("\033[0;32menv is available.\033[0m\n");
	else
		printf("\033[0;31menv has failed.\033[0m\n");
	if (cmd->exp)
		printf("\033[0;32mexport is available.\033[0m\n");
	else
		printf("\033[0;31mexport has failed.\033[0m\n");
	if (cmd->path)
		printf("PATH: %s\n", cmd->path);
	else
		printf("\033[0;31mpath has failed.\033[0m\n");
	printf("-------------------------\n");
	printf("Command: \"%s\"\n", cmd->cmd);
	if (cmd->arg[0] != NULL)
	{
		while (cmd->arg[++i] != NULL)
			printf("	Arg[%d]: \"%s\"\n", i, cmd->arg[i]);
	}
	else
		printf("Arguments: None\n");
	printf("-------------------------\n");
}

int	pop_help(t_env *cmds, int i)
{
	if (apply_fd(cmds) == 1)
		return (1);
	if (i == 0)
		cmds->exit_status = check_builtin(cmds);
	duping(cmds);
	return (0);
}

int	pop(t_env *cmds, int i)
{
	pid_t	pid;

	if (cmd_check(cmds) == 0)
		return (pop_help(cmds, i));
	pid = fork();
	if (pid == 0)
	{
		if (apply_fd(cmds) == 1)
			exit(1);
		if (i == 0)
			exit(check_builtin(cmds));
		exit(1);
	}
	else if (pid > 0)
		handle_parent(pid, cmds);
	else
		perror("fork failed");
	duping(cmds);
	return (cmds->exit_status);
}

int	fd_error(char *str)
{
	ft_putstr_fd(str, 2);
	write(2, " redirection error.", 19);
	write(2, "\n", 1);
	return (1);
}
