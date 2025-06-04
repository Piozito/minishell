/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:11:53 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:25:56 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '\0')
		input[0] = '\0';
}

void	free_env(char **array, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i == 0)
		return (free(array));
	else
	{
		i = 0;
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}

void	main_loop(t_env *cmds)
{
	char	*input;

	while (1)
	{
		initialize_cmd(cmds, NULL, 1);
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("./minishell: ");
		if (input == NULL)
			break ;
		signal(SIGQUIT, ft_noint_handler);
		signal(SIGINT, ft_noint_handler);
		check_input(input);
		if (*input != '\0')
		{
			add_history(input);
			pipes_handler(cmds, input);
			ft_cmds_free(cmds);
			duping(cmds);
		}
		free(input);
	}
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*cmds;

	(void)argv;
	if (argc != 1)
		general_error("Minishell doesn't take args", 0, 1, NULL);
	cmds = (t_env *)malloc(sizeof(t_env));
	cmds->exp = deep_copy_environ(env);
	cmds->env = deep_copy_environ(env);
	cmds->exit_status = 0;
	main_loop(cmds);
	write(2, "exit\n", 5);
	free_env(cmds->env, env);
	free_env(cmds->exp, env);
	duping(cmds);
	ft_cmds_free(cmds);
	free(cmds);
	rl_clear_history();
}
