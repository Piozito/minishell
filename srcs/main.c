/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 16:44:34 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	// Check for relative or absolute path
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return strdup(cmd);

	i = -1;
	allpath = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (NULL);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = my_get_path(s_cmd[0]);
	if (path == NULL)
	{
		printf("command not found: \"%s\"\n", s_cmd[0]);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		perror("execve");
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void ft_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
    char *input;
	char **args;

	(void)argc;
	(void)argv;
	if(argc != 1)
		return 0;

	t_env cmds;
	cmds.path = getenv("PATH");
	cmds.env = envp;

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
			else if(ft_strcmp(args[0], "cd") == 0)
				ft_cd(&cmds, args);
			else if(ft_strcmp(args[0], "env") == 0)
				ft_env(&cmds);
			else if(ft_strcmp(args[0], "exit") == 0)
				ft_exit(args);
			else if(ft_strcmp(args[0], "unset") == 0)
				ft_unset(&cmds, args);
			else
				exec(*args, cmds.env);
			free(input);
		}
    }
	rl_clear_history();
	free(args);
}