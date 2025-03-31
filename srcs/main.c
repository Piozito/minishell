/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/31 11:20:11 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void ft_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
    char *input;
	(void)argc;
	(void)argv;
	if(argc != 1)
		return 0;

	t_env cmds;
	cmds.path = getenv("PATH");
	cmds.env = envp;
	cmds.flag[0] = NULL;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
    {
        input = readline("./minishell: ");
        if(input == NULL)
			exit(0);
		else if(*input != '\0')
		{
			parsing(input, &cmds);
			add_history(input);
			if(ft_strcmp(cmds.cmd, "echo") == 0)
				ft_echo(&cmds);
			else if(ft_strcmp(cmds.cmd, "pwd") == 0)
				ft_pwd();
			else if(ft_strcmp(cmds.cmd, "cd") == 0)
				ft_cd(&cmds);
			else if(ft_strcmp(cmds.cmd, "env") == 0)
				ft_env(&cmds);
			else if(ft_strcmp(cmds.cmd, "exit") == 0)
				ft_exit(&cmds);
			else if(ft_strcmp(cmds.cmd, "unset") == 0)
				ft_unset(&cmds);
			/* else if(ft_strcmp(cmds.cmd, "export") == 0)
				ft_export(&cmds); */
			else
				ft_exec(&cmds);
			free(input);
		}
    }
	rl_clear_history();
}
