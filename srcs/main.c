/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:11:53 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/09 09:46:46 by aaleixo-         ###   ########.fr       */
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

int	check_builtin(t_env *cmds)
{
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		return ft_echo(cmds);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0)
		return ft_pwd(cmds);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		return ft_cd(cmds);
	else if (ft_strcmp(cmds->cmd, "env") == 0)
		return ft_env(cmds);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		return ft_exit(cmds);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		return ft_unset(cmds);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		return ft_export(cmds);
	else
		return ft_exec(cmds);
}

void	ft_cmds_free(t_env *cmds)
{
	int	i;

	if (cmds->cmd)
		free(cmds->cmd);
	if (cmds->flag)
	{
		i = 0;
		while (cmds->flag[i])
			free(cmds->flag[i++]);
		free(cmds->flag);
	}
	if (cmds->arg)
	{
		i = 0;
		while (cmds->arg[i])
			free(cmds->arg[i++]);
		free(cmds->arg);
	}
}

void	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '	')
		i++;
	if (input[i] == '\0')
		input[0] = '\0';
}

int	main()
{
	char	*input;
	t_env	*cmds;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	cmds = (t_env *)malloc(sizeof(t_env));
	cmds->exp = deep_copy_environ();
	cmds->env = deep_copy_environ();
	cmds->exit_status = 0;
	while (1)
	{
		initialize_cmd(cmds, NULL, 1);
		input = readline("./minishell: ");
		if (input == NULL)
		{
			free(input);
			rl_clear_history();
			break;
		}
		check_input(input);
		if (*input != '\0')
		{
			pipes_handler(cmds, input);
			add_history(input);
		}
		free(input);
		ft_cmds_free(cmds);
	}
	int i = 0;
	if (cmds->env)
	{
		i = 0;
		while (cmds->env[i])
			free(cmds->env[i++]);
		free(cmds->env);
	}
	if (cmds->exp)
	{
		i = 0;
		while (cmds->exp[i])
			free(cmds->exp[i++]);
		free(cmds->exp);
	}
}
