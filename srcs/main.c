/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:11:53 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/04 09:41:10 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	check_builtin(t_env *cmds)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		ft_pwd(cmds);
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
			rl_clear_history();
			exit(0);
		}
		else if (ft_strchr(input, '|') != NULL)
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
}
