/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 16:00:31 by aaleixo-         ###   ########.fr       */
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

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return ft_strdup(cmd);

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

void parsing(const char *input, t_env commands[], int num_commands) 
{
    char **tokens = ft_split(input, '|');
    num_commands = 0;
    int i = 0;
    while (tokens[i] != NULL && num_commands < MAX_COMMANDS)
	{
        t_env *cmd = &commands[(num_commands)++];
        char **subtokens = ft_split(tokens[i], ' ');
        int flag_index = 0;
        int arg_index = 0;
        int command_set = 0;
        int j = 0;
        while (subtokens[j] != NULL)
		{
            if (!command_set)
			{
                cmd->cmd = ft_strdup(subtokens[j]);
                command_set = 1;
            } 
			else if (subtokens[j][0] == '-') 
                cmd->flag[flag_index++] = ft_strdup(subtokens[j]);
			else
                cmd->arg[arg_index++] = ft_strdup(subtokens[j]);
            j++;
        }
        cmd->flag[flag_index] = NULL;
        cmd->arg[arg_index] = NULL;
        int k = 0;
        while (subtokens[k] != NULL)
		{
            free(subtokens[k]);
            k++;
        }
        free(subtokens);
        i++;
    }
    i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

int space_check(const char *input)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
            check++;
        i++;
    }
    return check;
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
			parsing(input, &cmds, space_check(input));
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
			else if(ft_strcmp(cmds.cmd, "export") == 0)
				ft_export(&cmds);
			else
				exec(cmds.cmd, cmds.env);
			free(input);
		}
    }
	rl_clear_history();
}
