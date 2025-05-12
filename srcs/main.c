/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:11:53 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/09 20:21:26 by aaleixo-         ###   ########.fr       */
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
	if(cmds->cmd == NULL)
		return 127;
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

	while(cmds)
	{
		if (cmds->cmd)
			free(cmds->cmd);
		if (cmds->arg)
		{
			i = 0;
			while (cmds->arg[i])
				free(cmds->arg[i++]);
			free(cmds->arg);
		}
		cmds = cmds->next;
	}
}

void	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '\0')
		input[0] = '\0';
}

void general_error(char *str, int free, int ex, t_env *cmds)
{
	if(free == 1)
		ft_cmds_free(cmds);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	if(ex == 1)
		exit(1);
}

void free_env(char **array, char **env)
{
	int i;

	i = 0;
	while(env[i] != NULL)
		i++;
	if(i == 0)
		return (free(array));
	else
	{
		i = 0;
		while(array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_env	*cmds;

	(void)argv;
	if(argc != 1)
		general_error("Minishell doesn't take args", 0, 1, NULL);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	cmds = (t_env *)malloc(sizeof(t_env));
	cmds->exp = deep_copy_environ(env);
	cmds->env = deep_copy_environ(env);
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
	if(env[0] == NULL)
		write(1, "\n", 1);
	free_env(cmds->env, env);
	free_env(cmds->exp, env);
}
