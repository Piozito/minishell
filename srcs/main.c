/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 17:07:35 by aaleixo-         ###   ########.fr       */
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

void	ft_exec(t_env *command)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		arg_count;
	char	**exec_args;
	int		i;
	int		j;

	i = 0;
	arg_count = 0;
	while (command->arg[arg_count] != NULL)
		arg_count++;
	while (command->flag[i] != NULL)
	{
		arg_count++;
		i++;
	}
	exec_args = malloc((arg_count + 2) * sizeof(char *));
	if (!exec_args)
	{
		perror("malloc");
		exit(1);
	}
	exec_args[0] = command->cmd;
	i = 0;
	while (command->flag[i] != NULL)
	{
		exec_args[i + 1] = command->flag[i];
		i++;
	}
	j = 0;
	while (command->arg[j] != NULL)
	{
		exec_args[i + 1] = command->arg[j];
		j++;
		i++;
	}
	exec_args[arg_count + 1] = NULL;
	path = my_get_path(command->cmd);
	if (path == NULL)
	{
		printf("command not found: \"%s\"\n", command->cmd);
		free(exec_args);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(exec_args);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, exec_args, command->env) == -1)
		{
			perror("execve");
			free(exec_args);
			exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
	free(exec_args);
}

void ft_handler()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void parsing(const char *input, t_env *cmd)
{
	char **subtokens = ft_split(input, ' ');
	int flag_index = 0;
	int arg_index = 0;
	int command_set = 0;
	int j = 0;

	cmd->cmd = NULL;
	for (int i = 0; i < MAX_FLAGS; i++)
		cmd->flag[i] = NULL;
	for (int i = 0; i < MAX_ARGS; i++)
		cmd->arg[i] = NULL;

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

	for (int k = 0; subtokens[k] != NULL; k++)
		free(subtokens[k]);
	free(subtokens);
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
			 else if(ft_strcmp(cmds.cmd, "export") == 0)
				ft_export(&cmds); 
			else
				ft_exec(&cmds);
			free(input);
		}
    }
	rl_clear_history();
}
