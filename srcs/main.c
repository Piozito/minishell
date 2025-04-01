/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/04/01 17:08:03 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	check_builtin(t_env *cmds)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds);
	else if (ft_strcmp(cmds->cmd, "env") == 0)
		ft_env(cmds);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(cmds);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds);
	else
		ft_exec(cmds);
}

void ft_cmds_free(t_env *cmds)
{
	int i;

	i = 0;
	if(cmds->cmd)
		free(cmds->cmd);
	while (i < MAX_FLAGS)
	{
		if (cmds->flag[i] != NULL)
			free(cmds->flag[i]);
		if (cmds->arg[i] != NULL)
			free(cmds->arg[i]);
		i++;
	}
}

void pipes_handler(t_env *cmds, char *input)
{
	char **pipes;
	t_env *temp;
	int i;

	temp = cmds;
	pipes = ft_split(input, '|');
	i = 0;
	while(pipes[i] != NULL)
	{
		parsing(pipes[i], temp);
		temp = temp->next;
		i++;
		printf("a");
	}
	ft_pipe(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	cmds;

	if (argc != 1)
		return (0);
	(void)argc;
	(void)argv;
	cmds.path = getenv("PATH");
	cmds.env = envp;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		initialize_cmd(&cmds);
		input = readline("./minishell: ");
		if (input == NULL)
		{
			free(input);
			ft_cmds_free(&cmds);
			exit(0);
		}
		else if (ft_strchr(input, '|'))
		{
			pipes_handler(&cmds, input);
			add_history(input);
		}
		else if (*input != '\0')
		{
			parsing(input, &cmds);
			add_history(input);
			check_builtin(&cmds);
		}
		free(input);
		ft_cmds_free(&cmds);
	}
	rl_clear_history();
}
