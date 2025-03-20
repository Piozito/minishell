/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/20 16:53:58 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void ft_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int main()
{
    char *input;
	char **args;
    
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
    {
        input = readline("./minishell: ");
        if(input == NULL)
			exit(0);
		else if(*input != '\0')
		{
			add_history(input);
			args = ft_split(input, ' ');
			if(ft_strcmp(args[0], "echo") == 0)
				ft_echo(args);
			else if(ft_strcmp(args[0], "pwd") == 0)
				ft_pwd();
			free(input);
		}
    }
	rl_clear_history();
	free(args);
}
