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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
