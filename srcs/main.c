/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:11:53 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/15 15:49:15 by aaleixo-         ###   ########.fr       */
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
    int i = 0;

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

void check_input(char *input)
{
	int i = 0;
	while(input[i] == ' ' || input[i] == '	')
		i++;
	if(input[i] == '\0')
		input[0] = '\0';
}

int	main()
{
	char	*input;
	extern char **environ;
	t_env	cmds;


	cmds.env = environ;
	cmds.path = getenv("PATH");
	if(environ[0] == NULL)
	{
		printf("No enviroment variables available.\n");
		exit(0);
	}
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
		check_input(input);
		if (*input != '\0')
		{
			pipes_handler(&cmds, input);
			add_history(input);
		}
		free(input);
		ft_cmds_free(&cmds);
	}
}
